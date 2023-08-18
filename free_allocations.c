/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_allocations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:41:01 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/17 17:20:38 by yichiba          ###   ########.fr       */
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

void	ft_free(t_lex *lexer, t_pars *parser, char **input)
{
	t_lex	*tmp;
	t_pars	*tmp2;

	if (parser && parser->args_num == 0 && !parser->red)
			lexer = NULL;
	while (lexer && lexer->content)
	{
		tmp = lexer;
		lexer = lexer->next;
		free(tmp->content);
		free(tmp);
	}
	while (parser)
	{
		tmp2 = parser;
		parser = parser->next;
		if (tmp2->red)
			free_redir(tmp2->red);
		free_double_ptr(tmp2->full_cmd);
		free(tmp2);
	}
	free(*input);
}

void	ft_free_g_global(t_g_global *g_global, t_pars *parser)
{
	(void)parser;
	free(g_global->pids);
}
