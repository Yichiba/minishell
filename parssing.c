/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:05:20 by ybourais          #+#    #+#             */
/*   Updated: 2023/07/10 12:06:17 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_error(int n)
{
    if(n == 1)
    {
        write(n, "Error\n", 6);
        exit(0);
    }
}

void check_quoting(char *str)
{
    int i;
    int j = 0;
    int quote;

    i = 0;
    while (str[i] != '\0')
    {
		while(str[i] == ' ' && (str[i + 1] == ' ' || str[i+1] == '\0'))
			i++;
        if (str[i] == '$' && str[i+1] != ' ')
            str[j] = '`';
        else if (str[i] != 34 && str[i] != 39)
            str[j] = str[i];
        else if(str[i] == 34 || str[i] == 39)
        {
            quote = str[i++];
            while (str[i] != quote)
            {
                if(str[i] == '\0')
                    ft_error(1);
                else if(str[i] == '$' && quote == 34)
                	{
						str[j++] = '`';
						 i++;
					}
				else
                	str[j++] = str[i++];
            }
            j--;
        }
        i ++;    
        j ++;
    }
    str[j] = '\0';
}

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

