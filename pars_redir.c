/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:13:37 by yichiba           #+#    #+#             */
/*   Updated: 2023/07/25 20:11:35 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_red	*ft_add_red(t_red *red, char *file, int type)
{
	t_red *new = malloc(sizeof(t_red));
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

t_red *ft_red(t_lex *lexer)
{
	t_lex *tmp = lexer;
	t_red *red = NULL;

	while (tmp && tmp->next && tmp->type != PIPE)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT || tmp->type == DREDIR_OUT || tmp->type == HERE_DOC)
		{
			red = ft_add_red(red, tmp->next->content, tmp->type);
			lexer = remove_node(lexer, tmp->next);
			lexer = remove_node(lexer, tmp);
		}
		tmp = tmp->next;
	}
	return red;
}

int		ft_syntax_redir(t_lex *lexer)
{
	t_lex *tmp;
	tmp  = lexer;
	while(tmp && tmp->next)
	{
		if(tmp->type == REDIR_IN || tmp->type == REDIR_OUT || tmp->type == DREDIR_OUT || tmp->type == HERE_DOC)
			if (!tmp->next || tmp->next->type != WORD)
				{
					printf("syntax error near unexpected token `%s'\n", tmp->next->content);
					return(0);
				}
		  	
				tmp = tmp->next;
	}
	return(1);
}