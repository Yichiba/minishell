/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:56:06 by yichiba           #+#    #+#             */
/*   Updated: 2023/07/25 19:59:06 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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