/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:13:37 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/06 12:01:20 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_red	*ft_add_red(t_red *red, char *file, int type)
{
	t_red *new = ft_calloc(1, sizeof(t_red));
	if (!new)
		return red;
	new->file = ft_strdup(file);
	new->type = type;
	new->next = NULL;
	if (!red) {
		return new;
	}
	t_red *tmp = red;
	while (tmp->next) {
		tmp = tmp->next;
	}

	tmp->next = new;

	return red;
}


t_red *ft_red(t_lex *lexer,t_lex **start)
{
	t_lex *tmp = lexer;
	t_red *red = NULL;
	t_lex *ptr;
	t_lex *ptr2;
	if(tmp->type == REDIR_IN || tmp->type == REDIR_OUT || tmp->type == DREDIR_OUT || tmp->type == HERE_DOC)
		*start = tmp->next->next;
	else
		*start = lexer;
	while (tmp && tmp->next && tmp->type != PIPE)
	{	
		ptr = tmp->next;
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT || tmp->type == DREDIR_OUT || tmp->type == HERE_DOC)
		{
			ptr = tmp->next->next;
			ptr2 = tmp->next->next;
			red = ft_add_red(red, tmp->next->content, tmp->type);
			lexer = remove_node(lexer, tmp->next);
			lexer = remove_node(lexer, tmp);
			if(!ptr)
				break ;
		}
		tmp = ptr;
	}
	return red;
}

// int		ft_syntax_redir(t_lex *lexer)
// {
// 	t_lex *tmp;
// 	tmp  = lexer;
// 	t_lex *start;
// 	while(tmp && tmp->next)
// 	{
// 		start = tmp;
// 		if(tmp->type == REDIR_IN || tmp->type == REDIR_OUT || tmp->type == DREDIR_OUT || tmp->type == HERE_DOC)
// 			if (!tmp->next || (tmp->next->type != WORD && tmp->next->type != VAR))
// 				{
// 					printf("syntax error near unexpected token `%s'\n", tmp->next->content);
// 					return(0);
// 				}
		  	
// 		tmp = tmp->next;
// // 	}
// 	if(tmp->type == REDIR_IN || tmp->type == REDIR_OUT || tmp->type == DREDIR_OUT || tmp->type == HERE_DOC)
// 	{
// 		printf("syntax error near unexpected token `%s'\n", tmp->content);
// 		return(0);
// 	}
// 	return(1);
// }