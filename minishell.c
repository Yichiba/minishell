/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:13:38 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/05 22:09:06 by yichiba          ###   ########.fr       */
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
	var = ft_calloc(j + 2, sizeof(char));
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
		else if(input[*i] == '?')
			return(ft_strdup("$?"));
		else if(input[*i] == ' ')
			return(ft_strdup("$ "));
		else if(ft_num(input[*i]))
		{
			var[0] = '$';
			var[1] = input[*i];
			var[2] = '\0';
			return(ft_strdup(var));
		}
		else if( ft_alpha(input[*i] ) || input[*i] == '_')
			return(set_var( input, i));
		else
			{
				*i = *i - 1;
				return(ft_strdup("$"));
			}
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
	tmp = ft_calloc(ft_strlen(str) + ft_strlen(tab) + 1, sizeof(char));
	while(str && str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	if(str)
		free(str);
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
	char 	**cmd = NULL;
	int i = 0;
	t_lex *tmp;
	tmp= start;
	if(!tmp)
		return(NULL);
	cmd = ft_calloc((args +1) , sizeof(char *));
	while(tmp && tmp->type != PIPE )
	{
		cmd[i++] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	cmd[i] = NULL;
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

void	free_double_ptr(char **str)
{
	int i = 0;
	while(str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);	
}

void	free_redir(t_red *red)
{
	t_red *tmp;
	while(red)
	{
		tmp = red;
		red = red->next;
		free(tmp->file);
		free(tmp);
	}
}

void	ft_free(t_lex *lexer, t_pars *parser)
{
	t_lex *tmp;
	t_pars *tmp2;
	if(parser && parser->args_num == 0)
		lexer = NULL;
	while(lexer && lexer->content )
	{
		tmp = lexer;
		lexer = lexer->next;
		free(tmp->content);
		free(tmp);
	}
	if(parser)
		free_redir(parser->red);
	while(parser)
	{
		tmp2 = parser;
		parser = parser->next;
		free_double_ptr(tmp2->full_cmd);
		free(tmp2);
	}
}


int main(int ac, char **av, char **environ)
{
	t_lex *lexer = NULL;
	t_pars *parser = NULL;
	g_exit = 0;
    char *input;
	
	(void)ac;
	(void)av;
    t_env *env = NULL;
    env = get_env(environ);
	parser = NULL;
	parser = NULL ;
    while(1)
    {
        input = readline("\e[1;53mMiniShell$ \e[0m");
		add_history(input);
		if (input == NULL)
			exit(g_exit);
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue;
		}
		lexer = ft_lexer(input);
		lexer = ft_clean(lexer,env);
		parser = ft_parser(lexer);
		if(parser && parser->args_num == 0)
			lexer = NULL;
		ft_excutions(parser,env);
		ft_free(lexer,parser);
		free(input);
    }
    return 0;
}