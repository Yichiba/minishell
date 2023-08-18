/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_outils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:10:17 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/17 16:04:14 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lex	*ft_match(t_lex *lexer)
{
	t_lex	*tmp;

	tmp = lexer;
	while (tmp && tmp->next)
	{
		if ((tmp->type == WORD && tmp->state == GENERAL)
			&& (tmp->next->type == WORD && tmp->next->state == GENERAL))
		{
			tmp->content = ft_strjoin(tmp->content, tmp->next->content);
			lexer = remove_node(lexer, tmp->next);
			tmp = lexer;
		}
		else if ((tmp->type == WORD && tmp->state == IN_DQUOTE)
			&& (tmp->next->type == WORD && tmp->next->state == IN_DQUOTE))
		{
			tmp->content = ft_strjoin(tmp->content, tmp->next->content);
			lexer = remove_node(lexer, tmp->next);
			tmp = lexer;
		}
		tmp = tmp->next;
	}
	return (lexer);
}

t_lex	*ft_remove_quote(t_lex *lexer)
{
	t_lex	*tmp;
	t_lex	*tmp2;

	tmp = lexer;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (tmp->type == QUOTE || tmp->type == DOUBLE_QUOTE)
			lexer = remove_node(lexer, tmp);
		tmp = tmp2;
	}
	ft_match(lexer);
	return (lexer);
}

t_lex	*remove_node(t_lex *lex, t_lex *node)
{
	t_lex	*next_node;
	t_lex	*tmp;

	if (lex == node)
	{
		next_node = lex->next;
		free(lex->content);
		free(lex);
		lex = NULL;
		return (next_node);
	}
	tmp = lex;
	while (tmp && tmp->next != node)
		tmp = tmp->next;
	next_node = NULL;
	if (tmp)
	{
		if (tmp->next->next)
			next_node = tmp->next->next;
		free(tmp->next->content);
		free(tmp->next);
		tmp->next = next_node;
	}
	return (lex);
}

char	*look_for_var(t_env *env, char *var_name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(var_name, tmp->var) == 1)
		{
			free(var_name);
			return (tmp->str);
		}
		tmp = tmp->next;
	}
	free(var_name);
	return ("");
}

t_lex	*ft_clean(t_lex *lexer, t_env *env)
{
	t_lex	*tmp;

	lexer = ft_expand_variables(lexer, env);
	lexer = ft_remove_quote(lexer);
	tmp = lexer;
	while (tmp && tmp->next)
	{
		if ((tmp->type == VAR && tmp->next->type == WORD)
			|| (tmp->state == IN_QUOTE && tmp->next->state == IN_QUOTE)
			|| (tmp->state == IN_DQUOTE && tmp->type != VAR
				&& tmp->next->type != VAR && tmp->next->state == IN_DQUOTE)
			|| (tmp->type == WORD && tmp->next->type == WORD))
		{
			tmp->content = ft_strjoin(tmp->content, tmp->next->content);
			lexer = remove_node(lexer, tmp->next);
		}
		else
			tmp = tmp->next;
	}
	lexer = ft_remove_space(lexer);
	lexer = ft_syntax(lexer);
	return (lexer);
}
