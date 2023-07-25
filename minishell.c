/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:13:38 by yichiba           #+#    #+#             */
/*   Updated: 2023/07/25 20:25:18 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_alpha(char str)
{
	if(str >= 'a' && str <= 'z')
		return(1);
	else if(str >= 'A' && str <= 'Z')
		return(1);
	else
		return(0);
}

int ft_num(char str)
{
	if(str >= '0' && str <= '9')
		return(1);
	else
		return(0);
}

char *set_var(char *input,int *i)
{
	int j = 0;
	char *var;
	while(ft_alpha(input[*i+j]) || ft_num(input[*i+j]) || input[*i+j] == '_')
		j++;
	var = malloc(j + 2);
	j = 0;
	var[j++] = '$';
	while(ft_alpha(input[*i]) || ft_num(input[*i]) || input[*i] == '_')
		var[j++] = input[(*i)++];
	var[j] = '\0';
	(*i)--;
	return(var);
}

char *ft_dollar(char *input, int *i)
{
	char var[10];
	while(input[*i])
	{
		(*i)++;
		if(input[*i] == '$')
			return(ft_strdup("$$"));
		if(input[*i] == '?')
			return(ft_strdup("$?"));
		if(input[*i] == ' ')
			return(ft_strdup("$ "));
		if(ft_num(input[*i]))
		{
			var[0] = '$';
			var[1] = input[*i];
			var[2] = '\0';
			return(ft_strdup(var));
		}
		if( ft_alpha(input[*i] ) || input[*i] == '_')
			return(set_var( input, i));
	}
	return(ft_strdup("$"));
}

int ft_strlen(char *str)
{
	int i = 0;
	while(str && str[i])
		i++;
	return(i);
}

char *ft_strjoin(char *str, char *tab)
{
	int i = 0;
	int j = 0;
	char *tmp;
	tmp = malloc(ft_strlen(str) + ft_strlen(tab) + 1);
	while(str && str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	while(tab && tab[j])
	{
		tmp[i] = tab[j];
		i++;
		j++;
	}
	tmp[i] = '\0';
	return(tmp);
}

char **get_full_cmd(t_lex *start,int args)
 {
	char 	**cmd;
	int i = 0;
	t_lex *tmp;
	tmp= start;
	cmd = malloc(args * sizeof(char *));
	while(tmp  && tmp->type != PIPE )
	{
		cmd[i++] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	return(cmd);
 }
 
 int count_pipes(t_lex *lexer)
 {
	 int i = 0;
	 while(lexer)
	 {
		 if(lexer->type == PIPE)
			i++;
		lexer = lexer->next;
	 }
	 return(i+1);
 }

int main(int ac, char **av, char **environ)
{
	t_lex *lexer = NULL;
	t_pars *parser = NULL;
    char *input;
	
	(void)ac;
	(void)av;
    t_env *env = NULL;
    env = ft_env(environ);
	parser = NULL;
	parser = NULL ;
    while(1)
    {
        input = readline("\e[1;53mMiniShell$ \e[0m");
		add_history(input);
		lexer = ft_lexer(input);
		lexer = ft_clean(lexer);
		ft_print_lexer(lexer);
		parser = ft_parser(lexer);
		// ft_print_parser(parser);
		free(input);
    }
    return 0;
}