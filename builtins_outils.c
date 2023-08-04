/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_outils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 12:04:45 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/02 14:09:38 by yichiba          ###   ########.fr       */
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
	else if (str[i] == '-' || str[i] == '+')
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

t_env	*ft_remove_node(t_env *env, char *data)
{
	t_env	*previous;
	t_env	*current;

	previous = NULL;
	current = env;
	while (current)
	{
		if (ft_strcmp(current->var, data))
		{
			if (previous == NULL)
			{
				env = current->next;
				free(current);
				current = env;
			}
			else
			{
				previous->next = current->next;
				free(current);
				return (env);
			}
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}
	return (env);
}

int	ft_strcmp(char *str, char *ptr)
{
	int	i;

	i = 0;
	if (!str || !ptr)
		return (0);
	while (str[i] || ptr[i])
	{
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
		if (!(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A'
				&& str[i] <= 'Z') && !(str[i] >= '0' && str[i] <= '9')
			&& str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
