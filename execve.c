/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:03:46 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/13 11:52:13 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_env_to_tab(t_env *env)
{
	char	**tab;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		if (tmp->var && tmp->str)
			i++;
		tmp = tmp->next;
	}
	tab = ft_calloc((i + 1), sizeof(char *));
	tmp = env;
	i = 0;
	while (tmp)
	{
		if (tmp->var && tmp->str)
			tab[i++] = ft_strjoiin(tmp->var, tmp->str, 1);
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

int	ft_is_builtins(char *str)
{
	if (ft_strcmp(str, "export") || ft_strcmp(str, "unset") || ft_strcmp(str,
			"cd") || ft_strcmp(str, "pwd") || ft_strcmp(str, "echo")
		|| ft_strcmp(str, "env") || ft_strcmp(str, "exit"))
		return (1);
	else
		return (0);
}

char	*ft_access(char **tab, char *cmd)
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	if (ft_strchr(cmd, '/') && access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
			write(2, "minishell : Permission denied", 29);
	}
	while (tab[i])
	{
		path = ft_strjoiin(tab[i], cmd, 0);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	printf("minishell: %s: command not found\n", cmd);
	exit(127);
	return (NULL);
}

t_env	*find_commands(t_env *env, t_pars *parser)
{
	char	**env_tab;
	char	*path;
	t_env	*tmp;
	char	**path_tab;

	env_tab = NULL;
	path = NULL;
	tmp = NULL;
	tmp = env;
	while (tmp)
	{
		if (tmp->var && ft_strcmp(tmp->var, "PATH"))
		{
			path = tmp->str;
			break ;
		}
		tmp = tmp->next;
	}
	env_tab = ft_env_to_tab(env);
	path_tab = ft_split(path, ':');
	path = ft_access(path_tab, parser->full_cmd[0]);
	if (path)
		execve(path, parser->full_cmd, env_tab);
	return (env);
}

// int _excution1(t_global *global,int i,t_pars *tmp,t_std *std)
// {
// 	if (global->fide.file == -5)
// 			exit(1);
// 		if (i > 0)
// 		{
// 			dup2(global->id, 0);
// 			close(global->id);
// 		}
// 		if (tmp->next)
// 		{
// 			dup2(global->fd[1], 1);
// 			close(global->fd[1]);
// 			close(global->fd[0]);
// 		}
// 		output = ft_redirections(tmp, &global->fide, std);
// }
