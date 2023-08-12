/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_outils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 11:07:44 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/12 12:12:28 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

t_lex	*ft_double_quote(t_lex *tmp)
{
	tmp = tmp->next;
	while (tmp && tmp->next && tmp->type != DOUBLE_QUOTE)
	{
		tmp->state = IN_DQUOTE;
		if (tmp->type != VAR)
			tmp->type = WORD;
		tmp = tmp->next;
	}
	return (tmp);
}

t_lex	*ft_quote(t_lex *tmp)
{
	tmp = tmp->next;
	while (tmp && tmp->next && tmp->type != QUOTE)
	{
		tmp->state = IN_QUOTE;
		tmp->type = WORD;
		tmp = tmp->next;
	}
	return (tmp);
}

t_lex	*ft_remove_space(t_lex *lexer)
{
	t_lex	*tmp;
	t_lex	*prev;
	t_lex	*to_remove;

	tmp = lexer;
	prev = NULL;
	while (tmp)
	{
		if (tmp->type == WHITE_SPACE)
		{
			to_remove = tmp;
			tmp = tmp->next;
			if (prev)
				prev->next = tmp;
			else
				lexer = tmp;
			free(to_remove->content);
			free(to_remove);
		}
		else
			tmp = ((prev = tmp), tmp->next);
	}
	return (lexer);
}

t_lex	*ft_set_state(t_lex *lexer)
{
	t_lex	*tmp;

	tmp = lexer;
	while (tmp && tmp->next)
	{
		if (tmp->type == DOUBLE_QUOTE)
			tmp = ft_double_quote(tmp);
		else if (tmp->type == QUOTE)
			tmp = ft_quote(tmp);
		else
			tmp->state = GENERAL;
		tmp = tmp->next;
	}
	return (lexer);
}
