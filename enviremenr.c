/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviremenr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:38:58 by yichiba           #+#    #+#             */
/*   Updated: 2023/07/25 19:19:17 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *set_variables(char*str)
{
	char *tab;
	int i = 0;
		while(str[i] && str[i] != '=')
			i++;
		tab = malloc(i+1);
		i = 0;
		while(str[i] && str[i] != '=')
			{
				tab[i] = str[i];
				i++;
			}
		tab[i] = '\0';	
	return(tab);
}

char *set_value(char*str)
{
	char *tab;
	int j = 0;
	int i = 0;
		while(str[i] && str[i] != '=')
			i++;
		if(str[i] == '\0')
			return(NULL);
		tab = malloc(strlen(str) - i);
		i++;
		while(str[i])
				tab[j++] = str[i++];
		tab[j] = '\0';	
	return(tab);
}

t_env *ft_add_back(char *str)
{
	t_env *node;

	node = malloc(sizeof(t_env));
	node->var = set_variables(str);
	node->str = set_value(str);
	node->next = NULL;
	return(node);
}

t_env *ft_env(char **tab)
{
	int i =0;
	t_env *head = NULL;
	t_env *ptr;
	
	head = ft_add_back(tab[i++]);
	ptr = head;
	while(tab[i])
	{
		ptr->next = ft_add_back(tab[i]);
		ptr =ptr->next;
		i++;
	}
	return(head);
}