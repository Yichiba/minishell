/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excutions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:47:14 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/07 22:10:13 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_putstr(char *str)
{
	int i = 0;
	while(str[i])
	{
		if(str[i] == '"' || str[i] == '$')
			write(1, "\\", 1);
		write(1, &str[i], 1);
		i++;
	}
}

t_env * ft_export(t_env *env, char **tab)
{
	int i = 1;
	char *var_name;
	t_env *ptr = env;
	if (!tab[1])
	{
		while (ptr)
		{
			if (!ptr->str)
				printf("declare -x %s\n", ptr->var);
			else
			{
				// if((ft_strchr(ptr->str, '$')) || (ft_strchr(ptr->str, '\"')))
				// 	{
						ft_putstr("declare -x ");
						ft_putstr(ptr->var);
						write(1, "=\"", 2);
						ft_putstr(ptr->str);
						write(1, "\"", 1);
						write(1, "\n", 1);
				// 	}
				// else
				// 	printf("declare -x %s=\"%s\"\n", ptr->var, ptr->str);
			}
			ptr = ptr->next;
		}
		g_exit = 0;
	}
	else
		while (tab[i])
		{
			var_name = set_variables_name(tab[i]);
			if (variable_syntax(var_name) == 0)
			{
				while (ptr)
				{
					if (ft_strcmp(ptr->var, var_name))
					{
						free(var_name);
						var_name = set_value(tab[i]);
						if(var_name)
							{
								free(ptr->str);
								ptr->str = var_name;
							}
						break;
					}
					if (!ptr->next)
						ptr->next = ft_add_back(tab[i]);
					ptr = ptr->next;
				}
				g_exit = 0;
			}
			else
			{
				write(2, "minishell: not a valid identifier", 33);
				// write(2, var_name, ft_strlen(var_name));
				write(2, "\n", 1);
				g_exit = 1;
			}
			i++;
		}
	return (env);
}

void ft_echo(char **tab)
{
	int newline = 0;
	int i = 1;

	while (tab[i])
	{
		int x = ft_strcmp(tab[i], "-n");
		if (x)
		{
			newline = 1;
				i++;
		}
		else
			while (tab[i])
			{
				printf("%s", tab[i]);
				i++;
				if (tab[i] != NULL)
					printf(" ");
			}
	}
	if (newline == 0)
		printf("\n");
	g_exit = 0;
}

void ft_env(t_env *env)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->str)
			printf("%s=%s\n", tmp->var, tmp->str);
		tmp = tmp->next;
	}
	g_exit = 0;
}

t_env *ft_unset(t_env *env, char **tab)
{
	int i = 1;
	char *var_name;
	while (tab[i])
	{
		var_name = set_variables_name(tab[i]);
		if (variable_syntax(var_name) == 0)
			{
				env = ft_remove_node(env, var_name);
				g_exit = 0;
			}
		else
			{
				write(2, "export: not valid in this context: ", 35);
				write(2, var_name, ft_strlen(var_name));
				write(2, "\n", 1);
				g_exit = 1;
			}
		i++;
	}
	return (env);
}

t_env *ft_pwd(t_env *env)
{
	char	*str;

	str = getcwd(NULL, 0);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	g_exit = 0;
	return (env);
}

t_env *ft_cd(t_env *env, char **tab)
{
	char *path;
	// char *oldpwd = getcwd(NULL, 0);

	if (!tab[1])
	{
		path = ft_getenv(env, "HOME");
		if (!path)
		{
			printf("cd: HOME not set\n");
			g_exit = 1;
			return (env);
		}
		else
			if (chdir(path) == -1)
			{
				write(2, "minishell: ", 11);
				write(2, "No such file or directory\n", 26);
				g_exit = 1;
				return (env);
			}
	}
	else
		{
			path = tab[1];
			if (chdir(path) == -1)
			{
				write(2, "minishell: ", 11);
				write(2, "No such file or directory\n", 26);
				g_exit = 1;
				return (env);
			}
		}
	return (env);
}
int ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
int 	ft_check_num(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
			i++;
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

t_env *ft_exit(t_env *env, char **tab)
{
	int i = 0;
	int num = 0;

	while (tab[i])
		i++;
	if (i == 1)
		exit(g_exit);
	else if ((i == 2) && (ft_check_num(tab[1]) == 0))
	{
		num = ft_atoi(tab[1]);
		exit(num);
	}
	else if ((i >= 2) && (ft_check_num(tab[1]) == 1))
	{
		printf("minishell: exit: %s: numeric argument required\n", tab[1]);
		exit(255);
	}
	else
	{
		printf("minishell: exit: too many arguments\n");
		g_exit = 1;
	}
	return (env);
}

t_env	*ft_builtins(t_pars *parser,t_env *env)
{
	if (ft_strcmp(parser->full_cmd[0], "export") == 1)
			env = ft_export(env, parser->full_cmd);
	else if (ft_strcmp(parser->full_cmd[0], "unset") == 1)
		env = ft_unset(env, parser->full_cmd);
	else if (ft_strcmp(parser->full_cmd[0], "cd") == 1)
		env = ft_cd(env, parser->full_cmd);
	else if (ft_strcmp(parser->full_cmd[0], "pwd") == 1)
		env = ft_pwd(env);
	else if (ft_strcmp(parser->full_cmd[0], "echo") == 1)
		ft_echo(parser->full_cmd);
	else if (ft_strcmp(parser->full_cmd[0], "env") == 1)
		ft_env(env);
	else if (ft_strcmp(parser->full_cmd[0], "exit") == 1)
		env = ft_exit(env, parser->full_cmd);
	return(env);
}

int ft_is_builtins(char *str)
{
	if(ft_strcmp(str,"export") || ft_strcmp(str,"unset") ||ft_strcmp(str,"cd") 
			||ft_strcmp(str,"pwd") ||ft_strcmp(str,"echo") ||ft_strcmp(str,"env" ) || ft_strcmp(str,"exit"))
				return(1);
	else
		return(0);
}

void	ft_wait(t_pars *parser,int *pids)
{
	int	status;

	t_pars *tmp = parser;
	int i = 0;
	while (tmp)
	{
		waitpid(pids[i], &status, 0);
		i++;
		tmp = tmp->next;
	}
	g_exit = status >> 8;
}
void	ft_pipe(int i,int *id,t_pars *tmp,t_env *env,int *fd)
{
	if (i > 0)
	{
		dup2(*id, 0);
		close (*id);
	}
	if (tmp->next)
	{
		dup2(fd[1], 1);
		close (fd[1]);
		close (fd[0]);
	}
	if(ft_is_builtins(tmp->full_cmd[0]))
	{
		ft_builtins(tmp, env);
		exit(0);
	}
	else
		find_commands(env, tmp);
}

t_env *ft_excutions(t_pars *parser, t_env *env)
{
	t_file fide;
	fide.file = -1;
	fide.std_in = -1;
	fide.std_out = -1;
	int fd[2];
	int id = -1;
	t_pars *tmp;
	int	i;
	int	pids[10];

	i = 0;
	tmp = parser;
	while (tmp)
	{
		if (!tmp || tmp->args_num == 0)
			return (env);
		if(ft_is_builtins(tmp->full_cmd[0]) && !tmp->next)
			{
				if (tmp->red)
					fide.file = ft_redirections(tmp->red, &fide);
				ft_builtins(tmp, env);
				if (tmp->red)
					close_file(tmp->red, &fide);
				return (env);
			}
		else
		{
			if (tmp->next)
				pipe(fd);
			pids[i] = fork();
			if (pids[i] == 0)
				{
					if (i > 0)
					{
						dup2(id, 0);
						close (id);
					}
					if (tmp->next)
					{
						dup2(fd[1], 1);
						close (fd[1]);
						close (fd[0]);
					}
					if(ft_is_builtins(tmp->full_cmd[0]))
					{
						if (tmp->red)
						fide.file = ft_redirections(tmp->red, &fide);	
						ft_builtins(tmp, env);
						if (tmp->red)
							close_file(tmp->red, &fide);
						exit(0);
					}
					else
						find_commands(env, tmp);
				}
				// ft_pipe(i,&id,tmp,env,fd);
			if (i > 0)
				close (id);
			if (tmp->next)
			{
				id = fd[0];
				close (fd[1]);
			}
		}
		if (tmp->red)
			close_file(tmp->red, &fide);
		i++;
		tmp = tmp->next;
	}
	if(parser)
		ft_wait(parser,pids);
	return (env);
}
