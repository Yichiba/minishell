/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:35:57 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/13 22:13:05 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_export(t_env *ptr)
{
	while (ptr)
	{
		if (!ptr->str)
			printf("declare -x %s\n", ptr->var);
		else
		{
			ft_putstr("declare -x ");
			ft_putstr(ptr->var);
			write(1, "=\"", 2);
			ft_putstr(ptr->str);
			write(1, "\"", 1);
			write(1, "\n", 1);
		}
		ptr = ptr->next;
	}
	g_glob.g_exit = 0;
}

void	ft_add_to_export(t_env *ptr, char **tab, int i, char *var_name)
{
	while (ptr)
	{
		if (ft_strcmp(ptr->var, var_name))
		{
			free(var_name);
			var_name = set_value(tab[i]);
			if (var_name)
			{
				free(ptr->str);
				ptr->str = var_name;
			}
			break ;
		}
		if (!ptr->next)
			ptr->next = ft_add_back(tab[i]);
		ptr = ptr->next;
	}
	g_glob.g_exit = 0;
}

t_env	*ft_export(t_env *env, char **tab)
{
	int		i;
	char	*var_name;
	t_env	*ptr;

	i = 1;
	ptr = env;
	if (!tab[1])
		ft_print_export(env);
	else
	{
		while (tab[i])
		{
			var_name = set_variables_name(tab[i]);
			if (variable_syntax(var_name) == 0)
				ft_add_to_export(ptr, tab, i, var_name);
			else
			{
				write(2, "minishell: not a valid identifier", 33);
				write(2, "\n", 1);
				g_glob.g_exit = 1;
			}
			i++;
		}
	}
	return (env);
}

void	*ft_remove_env(t_env *env, char *var_name)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = env;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, var_name))
		{
			if (prev == NULL)
				env = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->var);
			free(tmp->str);
			free(tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (env);
}

t_env	*ft_unset(t_env *env, char **tab)
{
	int		i;
	char	*var_name;

	i = 1;
	while (tab[i])
	{
		var_name = tab[i];
		if (variable_syntax(var_name) == 0)
		{
			env = ft_remove_env(env, var_name);
			g_glob.g_exit = 0;
		}
		else
		{
			write(2, "export: not valid in this context: ", 35);
			write(2, var_name, ft_strlen(var_name));
			write(2, "\n", 1);
			g_glob.g_exit = 1;
		}
		i++;
	}
	return (env);
}
