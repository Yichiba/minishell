/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:47:14 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/04 20:01:25 by yichiba          ###   ########.fr       */
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

t_env *ft_builtins(t_pars *parser, t_env *env)
{
	int file = -1;
	int std_out = -1;
	int std_in = -1;
	// int input = 0;
	while (parser)
	{
			if (parser->red)
				file = ft_redirections(parser->red, &std_in, &std_out);
			if(file == -5)
				return(env);
			if (ft_strcmp(parser->full_cmd[0], "export") == 1) // m	ainprocess
				env = ft_export(env, parser->full_cmd);
			else if (ft_strcmp(parser->full_cmd[0], "unset") == 1) ///////// mainprocess
				env = ft_unset(env, parser->full_cmd);
			else if (ft_strcmp(parser->full_cmd[0], "cd") == 1)   ///////
				env = ft_cd(env, parser->full_cmd);
			else if (ft_strcmp(parser->full_cmd[0], "exit") == 1) 
				env = ft_exit(env, parser->full_cmd);
			else if (ft_strcmp(parser->full_cmd[0], "pwd") == 1)
				env = ft_pwd(env);
			else if (ft_strcmp(parser->full_cmd[0], "echo") == 1)
				ft_echo(parser->full_cmd);
			else if (ft_strcmp(parser->full_cmd[0], "env") == 1)
				ft_env(env);
			else
				env = find_commands(env, parser);
			if (parser->red)
				close_file(file, parser->red, &std_in, &std_out);
		parser = parser->next;
	}
	return (env);
}
