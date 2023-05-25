/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:59:39 by ybourais          #+#    #+#             */
/*   Updated: 2023/05/24 19:38:59 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_word_count(char *str)
{
	int i = 0;
	int c = 0;
	while (str[i] != '\0')
	{
		if ((str[i] != ' ' && str[i + 1] == ' ') || (str[i] != ' ' && str[i + 1] == '\0'))
			c++;
		i++;
	}
	return c;
}

int word_lenth(char *str)
{
	int i = 0;
	while (str[i] == ' ' && str[i+1] == ' ')
		i ++;
	while (str[i] != ' ' && str[i] != '\0')
		i ++;
	return i;
}

char **ft_split(char *str)
{
	char **tab = malloc(sizeof(char *) * ft_word_count(str));

	int i = 0;
	int counter = 0;

	while (str[i] != '\0')
	{
		int j = 0;
		int lenth = word_lenth(str + i);
		tab[counter] = malloc(sizeof(char) * lenth + 1);
		if(str[i] == ' ')
			i++;
		while(str[i] != '\0' && str[i] == ' ')
			tab[counter][j++] = str[i++];
		while(str[i] != '\0' && str[i] != ' ')
			tab[counter][j++] = str[i++];
		tab[counter][j] = '\0';
		counter++;
	}
	for (int n = 0; n < ft_word_count(str); n++)
		printf("|%s|\n", tab[n]);
	return tab;
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    
    char *input;
    
    while(1)
    {
        input = readline("\e[1;32mmy_Shell-310$ \e[0m");
        add_history(input);
        check_quoting(input);
		printf("%s\n",input);
		printf("\n");
		ft_split(input);
    }
    return 0;
}
// e"c""""ho" "" "he"l"lo '' i'm"       ""   jjjj