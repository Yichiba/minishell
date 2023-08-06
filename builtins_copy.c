 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:47:14 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/04 20:35:13 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *ft_export(t_env *env, char **tab)
{
	int i = 1;
	char *var_name;
	t_env *ptr = env;
	if (!tab[1])
		while (ptr)
		{
			if (!ptr->str)
				printf("declare -x %s\n", ptr->var);
			else
				printf("declare -x %s=\"%s\"\n", ptr->var, ptr->str);
			ptr = ptr->next;
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
						free(ptr->str);
						ptr->str = set_value(tab[i]);
						break;
					}
					if (!ptr->next)
						ptr->next = ft_add_back(tab[i]);
					ptr = ptr->next;
				}
			}
			else
				printf("export: not valid in this context: %s\n", var_name);
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
		if (ft_strcmp(tab[i], "-n") == 1)
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
}

t_env *ft_unset(t_env *env, char **tab)
{
	int i = 1;
	char *var_name;
	while (tab[i])
	{
		var_name = set_variables_name(tab[i]);
		if (variable_syntax(var_name) == 0)
			env = ft_remove_node(env, var_name);
		else
			printf("export: not valid in this context: %s\n", var_name);
		i++;
	}
	return (env);
}

t_env *ft_pwd(t_env *env)
{
	printf("%s\n", getcwd(NULL, 0));
	return (env);
}

t_env *ft_cd(t_env *env, char **tab)
{
	char *path;
	if (!tab[1] || ft_strcmp(tab[1], "~"))
	{
		path = ft_getenv(env, "HOME");
		if (path)
			chdir(path);
	}
	else if (tab[1][0] == '-')
	{
		path = ft_getenv(env, "OLDPWD");
		if (path)
			chdir(path);
	}
	else
		chdir(tab[1]);
	return (env);
}

t_env *ft_exit(t_env *env, char **tab)
{
	int i = 0;
	while (tab[i])
		i++;
	printf("exit\n");
	if (i == 1)
		exit(0);
	else if (i == 1)
		exit(ft_atoi(tab[1])); // atoi  fiiiix it
	else if (i == 2 && ft_num(tab[1][0]))
		exit(ft_atoi(tab[1])); // atoi  fiiiix it
	else if (i > 1 && !ft_num(tab[1][0]))
	{
		printf("MiniShell: exit: %s: numeric argument required\n", tab[1]);
		exit(0);
	}
	else
		printf("MiniShell: exit: too many arguments\n");
	return (env);
}

t_env	*ft_builtins(t_pars *parser,t_env *env)
{
	if (ft_strcmp(parser->full_cmd[0], "export") == 1)
			env = ft_export(env, parser->full_cmd);
	else if (ft_strcmp(parser->full_cmd[0], "unset") == 1)///////// mainprocess
		env = ft_unset(env, parser->full_cmd);
	else if (ft_strcmp(parser->full_cmd[0], "cd") == 1) ///////
		env = ft_cd(env, parser->full_cmd);
	else if (ft_strcmp(parser->full_cmd[0], "pwd") == 1)
		env = ft_pwd(env);
	else if (ft_strcmp(parser->full_cmd[0], "echo") == 1)
		ft_echo(parser->full_cmd);
	else if (ft_strcmp(parser->full_cmd[0], "env") == 1)
		ft_env(env);
	else if (ft_strcmp(parser->full_cmd[0], "exit") == 1) ////////
		env = ft_exit(env, parser->full_cmd);
	// else
	// 	ft_pipe();
	return(env);
}

t_env *ft_excutions(t_pars *parser, t_env *env)
{
	int file = -1;
	int stdout = -1;
	int stdin = -1;
	int fd[2];
	int input = -1;
	t_pars *tmp;
	int id;
	int	i;
	int	pids[10];

	i = 0;
	tmp = parser;
	while (tmp)
	{
		if (!tmp || tmp->args_num == 0)
			return (env);
		if (tmp->red)
			file = ft_redirections(tmp->red, &stdin, &stdout);
		// ft_builtins(tmp, env);
		if (ft_strcmp(tmp->full_cmd[0], "export") == 1)
			env = ft_export(env, tmp->full_cmd);
		else if (ft_strcmp(tmp->full_cmd[0], "unset") == 1)///////// mainprocess
			env = ft_unset(env, tmp->full_cmd);
		else if (ft_strcmp(tmp->full_cmd[0], "cd") == 1) ///////
			env = ft_cd(env, tmp->full_cmd);
		else if (ft_strcmp(tmp->full_cmd[0], "pwd") == 1)
			env = ft_pwd(env);
		else if (ft_strcmp(tmp->full_cmd[0], "echo") == 1)
			ft_echo(tmp->full_cmd);
		else if (ft_strcmp(tmp->full_cmd[0], "env") == 1)
			ft_env(env);
		else if (ft_strcmp(tmp->full_cmd[0], "exit") == 1) ////////
			env = ft_exit(env, tmp->full_cmd);
		else
		{
			if (tmp->next)
				pipe(fd);
			pids[i] = fork();
			if (pids[i] == 0)
			{
				if (i > 0)
				{
					dup2(input, 0);
					close (input);
				}
				if (tmp->next)
				{
					dup2(fd[1], 1);
					close (fd[1]);
					close (fd[0]);
				}
				find_commands(env, tmp);
			}
			
			if (i > 0)
				close (input);
			if (tmp->next)
			{
				input = fd[0];
				close (fd[1]);
			}
		}
		if (tmp->red)
			close_file(file, tmp->red, &stdin, &stdout);
		i++;
		tmp = tmp->next;
	}
	tmp = parser;
	int	status;
	i = 0;
	while (tmp)
	{
		waitpid(pids[i], &status, 0);
		i++;
		tmp = tmp->next;
	}
	return (env);
}




// t_env	*ft_builtins(t_pars *parser,t_env *env)
// {
// 	if (ft_strcmp(parser->full_cmd[0], "export") == 1)
// 			env = ft_export(env, parser->full_cmd);
// 	else if (ft_strcmp(parser->full_cmd[0], "unset") == 1)///////// mainprocess
// 		env = ft_unset(env, parser->full_cmd);
// 	else if (ft_strcmp(parser->full_cmd[0], "cd") == 1) ///////
// 		env = ft_cd(env, parser->full_cmd);
// 	else if (ft_strcmp(parser->full_cmd[0], "pwd") == 1)
// 		env = ft_pwd(env);
// 	else if (ft_strcmp(parser->full_cmd[0], "echo") == 1)
// 		ft_echo(parser->full_cmd);
// 	else if (ft_strcmp(parser->full_cmd[0], "env") == 1)
// 		ft_env(env);
// 	else if (ft_strcmp(parser->full_cmd[0], "exit") == 1) ////////
// 		env = ft_exit(env, parser->full_cmd);
// 	return(env);
// }

// int ft_is_builtins(char *str)
// {
// 	if(ft_strcmp(str,"export") || ft_strcmp(str,"unset") ||ft_strcmp(str,"cd") 
// 			||ft_strcmp(str,"pwd") ||ft_strcmp(str,"echo") ||ft_strcmp(str,"env"))
// 				return(1);
// 	else
// 		return(0);
// }