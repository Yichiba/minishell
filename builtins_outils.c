/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_outils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majrou <majrou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 12:04:45 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/12 19:50:53 by majrou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

char	*ft_getenv(t_env *env, char *var)
{
	t_env	*ptr;

	ptr = env;
	while (ptr)
	{
		if (ft_strcmp(ptr->var, var))
			return (ptr->str);
		ptr = ptr->next;
	}
	return (NULL);
}

int	ft_strcmp(char *str, char *ptr)
{
	int	i;

	i = 0;
	if (!str || !ptr)
		return (0);
	while (str[i] || ptr[i])
	{
		if (str[i] != ptr[i] && str[i] == 'n')
			break ;
		if (str[i] != ptr[i])
			return (0);
		i++;
	}
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	variable_syntax(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (i == 0 && (str[i] >= '0' && str[i] <= '9'))
			return (1);
		if (!ft_alpha(str[i]) && !ft_num(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
