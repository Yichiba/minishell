/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_allocations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:41:01 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/11 15:00:31 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_ptr(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_redir(t_red *red)
{
	t_red	*tmp;

	while (red)
	{
		tmp = red;
		red = red->next;
		free(tmp->file);
		free(tmp);
	}
}

void	ft_free_lex(t_lex *lexer)
{
	t_lex	*tmp;

	while (lexer)
	{
		tmp = lexer;
		lexer = lexer->next;
		free(tmp->content);
		free(tmp);
	}
}

void	ft_free(t_lex *lexer, t_pars *parser)
{
	t_lex	*tmp;
	t_pars	*tmp2;

	if (parser && parser->args_num == 0)
		lexer = NULL;
	while (lexer && lexer->content)
	{
		tmp = lexer;
		lexer = lexer->next;
		free(tmp->content);
		free(tmp);
	}
	if (parser)
		free_redir(parser->red);
	while (parser)
	{
		tmp2 = parser;
		parser = parser->next;
		free_double_ptr(tmp2->full_cmd);
		free(tmp2);
	}
}
