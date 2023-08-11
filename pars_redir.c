/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:13:37 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/11 19:51:48 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_red	*ft_add_red(t_red *red, char *file, int type)
{
	t_red	*new;
	t_red	*tmp;

	new = ft_calloc(1, sizeof(t_red));
	if (!new)
		return (red);
	new->file = ft_strdup(file);
	new->type = type;
	new->next = NULL;
	if (!red)
	{
		return (new);
	}
	tmp = red;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
	return (red);
}

t_red	*ft_red(t_lex *lexer, t_lex **start)
{
	t_lex	*tmp;
	t_red	*red;
	t_lex	*ptr;
	t_lex	*ptr2;

	tmp = lexer;
	red = NULL;
	if (tmp_isredir(tmp))
		*start = tmp->next->next;
	else
		*start = lexer;
	while (tmp && tmp->next && tmp->type != PIPE)
	{
		ptr = tmp->next;
		if (tmp_isredir(tmp))
		{
			ptr = tmp->next->next;
			ptr2 = tmp->next->next;
			red = ft_add_red(red, tmp->next->content, tmp->type);
			if (!ptr)
				break ;
		}
		tmp = ptr;
	}
	return (red);
}
