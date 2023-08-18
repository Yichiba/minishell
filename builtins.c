/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:55:41 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/17 18:40:04 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '$')
			write(1, "\\", 1);
		write(1, &str[i], 1);
		i++;
	}
}

int	ft_check_num(char *str)
{
	int	i;

	i = 0;
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

void	print_exit(int num, char *tab)
{
	printf("exit\n");
	if (num == 0)
		exit(g_glob.g_exit);
	else if (num == 1)
	{
		num = ft_atoi(tab);
		exit(num);
	}
	else if (num == 2)
	{
		printf("minishell: exit: %s: numeric argument required\n", tab);
		exit(255);
	}
}

t_env	*ft_exit(t_env *env, char **tab)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (tab[i])
		i++;
	if (i == 1)
		print_exit(0, tab[1]);
	else if ((i == 2) && (ft_check_num(tab[1]) == 0))
		print_exit(1, tab[1]);
	else if ((i >= 2) && (ft_check_num(tab[1]) == 1))
		print_exit(2, tab[1]);
	else
	{
		printf("minishell: exit: too many arguments\n");
		g_glob.g_exit = 1;
	}
	return (env);
}

t_env	*ft_builtins(t_pars *parser, t_env *env)
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
	return (env);
}
