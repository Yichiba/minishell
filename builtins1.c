/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:44:44 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/13 22:13:05 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **tab)
{
	int	newline;
	int	i;
	int	x;

	newline = 0;
	i = 1;
	while (tab[i])
	{
		x = ft_strcmp(tab[i], "-n");
		if (x && i++)
			newline = 1;
		else
		{
			while (tab[i])
			{
				printf("%s", tab[i++]);
				if (tab[i] != NULL)
					printf(" ");
			}
		}
	}
	if (newline == 0)
		printf("\n");
	g_glob.g_exit = 0;
}

t_env	*ft_pwd(t_env *env)
{
	char	*str;

	str = getcwd(NULL, 0);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	g_glob.g_exit = 0;
	free(str);
	return (env);
}

void	ft_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->str)
			printf("%s=%s\n", tmp->var, tmp->str);
		tmp = tmp->next;
	}
	g_glob.g_exit = 0;
}

t_env	*ft_cd_(t_env *env, char **tab)
{
	char	*path;

	path = tab[1];
	if (chdir(path) == -1)
	{
		write(2, "minishell: ", 11);
		write(2, "No such file or directory\n", 26);
		g_glob.g_exit = 1;
		return (env);
	}
	return (env);
}

t_env	*ft_cd(t_env *env, char **tab)
{
	char	*path;

	if (!tab[1])
	{
		path = ft_getenv(env, "HOME");
		if (!path)
		{
			write(2, "minishell: ", 11);
			write(2, "cd: HOME not set\n", 17);
			g_glob.g_exit = 1;
			return (env);
		}
		else if (chdir(path) == -1)
		{
			write(2, "minishell: ", 11);
			write(2, "No such file or directory\n", 26);
			g_glob.g_exit = 1;
			return (env);
		}
	}
	else
		ft_cd_(env, tab);
	return (env);
}
