/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:05:20 by ybourais          #+#    #+#             */
/*   Updated: 2023/05/24 19:12:26 by yichiba          ###   ########.fr       */
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
		while(str[i] == ' ' && str[i + 1] == ' ')
			i++;
        if (str[i] != 34 && str[i] != 39)
            str[j] = str[i];
        else if(str[i] == 34 || str[i] == 39)
        {
            quote = str[i++];
            while (str[i] != quote)
            {
                if(str[i] == '\0')
                    ft_error(1);
                str[j++] = str[i++];
            }
            j--;
        }
        i ++;    
        j ++;
    }
    str[j] = '\0';
}