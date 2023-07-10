/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:59:39 by ybourais          #+#    #+#             */
/*   Updated: 2023/07/10 11:57:37 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int var_name(char *str)
{
	int i = 0;
	while(str[i] && str[i] != '=')
	{
		if(!(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A' && str[i] <= 'Z')
			 && !(str[i] >= '0' && str[i] <= '9') && !(str[i] == '_'))
			return(1);
		i++;	
	}
	return(0);
}

int ft_word_count(char *str)
{
	int i = 0;
	int c = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && ( str[i + 1] == ' ' ||str[i + 1] == '\0'))
			c++;
		i++;
	}
	return c;
}

int word_lenth(char *str)
{
	int i = 0;
	while (str[i] == ' ' )
		i ++;
	while (str[i] != ' ' && str[i] != '\0')
		i ++;
	return i;
}

char **ft_split(char *str)
{
	int i = 0;
	int counter = 0;
	int lenth;
	int j;

	char **tab = malloc(sizeof(char *) * (ft_word_count(str) + 1));
	while (str[i] != '\0')
	{
		j = 0;
		// if(str[i] == ' ' && counter == 0)
		// 	i++;
		lenth = word_lenth(str + i);
		tab[counter] = malloc(sizeof(char) * lenth + 1);
		while(str[i] == ' ')
			tab[counter][j++] = str[i++];
		while(str[i] != '\0' && str[i] != ' ')
				tab[counter][j++] = str[i++];
		if(str[i] == ' ')
			i++;
		tab[counter][j] = '\0';
		counter++;
		if(counter == ft_word_count(str))
			break;
	}
	tab[counter] = 0;
	return tab;
}
// t_env *parssing(char *str)
// {
// 	return 
// }

int main(int argc, char **argv,char **env)
{
    (void)argc;
    (void)argv;
    char *input;
	char **tab;
	t_env *envirment;
	
	envirment = ft_env(env);
    while(1)
    {
        input = readline("\e[12;32mbash-3.2$ \e[0m");
        add_history(input);
		parssing(input);
        // check_quoting(input);
		tab = ft_split(input);
		// for(int i = 0; tab[i]; i++)
		// 	printf("%s\n",tab[i]);
		envirment = ft_builtins(envirment, tab);
    }
}
