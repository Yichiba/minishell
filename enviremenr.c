/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviremenr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:38:58 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/11 17:03:32 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	void			*ptr;
	unsigned long	i;

	i = 0;
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	while (i < count * size)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

char	*set_variables_name(char *str)
{
	char	*tab;
	int		i;

	tab = NULL;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	tab = ft_calloc(i + 1, sizeof(char));
	i = 0;
	while (str[i] && str[i] != '=')
	{
		tab[i] = str[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	*set_value(char *str)
{
	char	*tab;
	int		j;
	int		i;

	j = 0;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (NULL);
	tab = ft_calloc(strlen(str) - i, sizeof(char));
	i++;
	while (str[i])
		tab[j++] = str[i++];
	tab[j] = '\0';
	return (tab);
}

t_env	*ft_add_back(char *str)
{
	t_env	*node;

	node = ft_calloc(1, sizeof(t_env));
	node->var = set_variables_name(str);
	node->str = set_value(str);
	node->next = NULL;
	return (node);
}

t_env	*get_env(char **tab)
{
	int		i;
	t_env	*head;
	t_env	*ptr;

	if (!tab[0])
		return (NULL);
	i = 0;
	head = ft_add_back(tab[i++]);
	ptr = head;
	while (tab && tab[i])
	{
		ptr->next = ft_add_back(tab[i]);
		ptr = ptr->next;
		i++;
	}
	return (head);
}
