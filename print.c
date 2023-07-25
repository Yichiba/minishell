/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:12:40 by yichiba           #+#    #+#             */
/*   Updated: 2023/07/25 20:10:21 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

 
char *get_state(enum e_state state)
{
	if(state == IN_DQUOTE)
		return("IN_DQUOTE");
	else if(state == IN_QUOTE)
		return("IN_QUOTE");
	else
		return("GENERAL");
}
char *get_type(enum e_token token)
{
	if(token == WHITE_SPACE)
		return("WHITE_SPACE");
	else if(token == QUOTE)
		return("QUOTE");
	else if(token == DOUBLE_QUOTE)
		return("DOUBLE_QUOTE");
	else if(token == ESCAPE)
		return("ESCAPE");
	else if(token == VAR)
		return("VAR");
	else if(token == PIPE)
		return("PIPE");
	else if(token == REDIR_IN)
		return("REDIR_IN");
	else if(token == REDIR_OUT)
		return("REDIR_OUT");
	else if(token == WORD)
		return("WORD");
	else if(token == HERE_DOC)
		return("HERE_DOC");
	else if(token == DREDIR_OUT)
		return("DREDIR_OUT");
	else
		return("ERROR");
}

void ft_print_lexer(t_lex *lexer)
{
	t_lex *tmp;

	tmp = lexer;
	if (tmp)
	{
		printf("tmp->content\t");
		printf("tmp->type\t");
		printf("tmp->state\n");
		printf("-------------------------------------------------\n");
	}
	while(tmp)
	{
		printf("%-10s\t", tmp->content);
		printf("%-10s\t", get_type(tmp->type));
		printf("%-10s\n", get_state(tmp->state));
		printf("-------------------------------------------------\n");
		tmp = tmp->next;
	}
}

void ft_print_red(t_red *red)
{
	t_red *tmp;
	tmp = red;
	while(tmp)
	{
		printf("%s      %s\n",get_type(tmp->type), tmp->file);
		tmp = tmp->next;
	}
}

void ft_print_parser(t_pars *parser)
{
	t_pars *tmp = parser;
	while(tmp)
	{
		for(int i = 0; i < tmp->args_num; i++)
			printf("%s\n",tmp->full_cmd[i]);
		printf("---------------------------------------------\n");
		ft_print_red(tmp->red);
		printf("---------------------------------------------\n");
		printf("%d\n",tmp->args_num);
		tmp = tmp->next;
	}
}