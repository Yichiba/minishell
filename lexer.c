/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:57:51 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/17 16:06:03 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *str)
{
	char	*tab;
	int		i;

	i = 0;
	tab = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		tab[i] = str[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

t_lex	*ft_add(t_lex *lex, char *content, enum e_token type)
{
	t_lex	*tmp;
	t_lex	*new;

	tmp = lex;
	new = ft_calloc(1, sizeof(t_lex));
	new->content = content;
	new->type = type;
	new->state = GENERAL;
	new->next = NULL;
	if (!tmp)
		return (new);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (lex);
}

void	*lexer_redirections(char *input, t_lex **lexer, int *i)
{
	if (input[*i + 1] && input[*i] == '<' && input[*i + 1] == '<')
	{
		(*i)++;
		*lexer = ft_add(*lexer, ft_strdup("<<"), HERE_DOC);
	}
	else if (input[*i] == '<')
		*lexer = ft_add(*lexer, ft_strdup("<"), REDIR_IN);
	else if (input[*i + 1] && input[*i] == '>' && input[*i + 1] == '>')
	{
		(*i)++;
		*lexer = ft_add(*lexer, ft_strdup(">>"), DREDIR_OUT);
	}
	else if (input[*i] == '>')
		*lexer = ft_add(*lexer, ft_strdup(">"), REDIR_OUT);
	return (*lexer);
}

void	ft_inside_lexer(char *input, int *i, t_lex **lexer)
{
	if (input[*i] == ' ')
		*lexer = ft_add(*lexer, ft_strdup(" "), WHITE_SPACE);
	else if (input[*i] == '\'')
		*lexer = ft_add(*lexer, ft_strdup("\'"), QUOTE);
	else if (input[*i] == '\"')
		*lexer = ft_add(*lexer, ft_strdup("\""), DOUBLE_QUOTE);
	else if (input[*i] == '$')
		*lexer = ft_add(*lexer, ft_dollar(input, i), VAR);
	else if (input[*i] == '|')
		*lexer = ft_add(*lexer, ft_strdup("|"), PIPE);
	else if (input[*i] == '<' || input[*i] == '>')
		*lexer = lexer_redirections(input, lexer, i);
	else
		*lexer = ft_add(*lexer, ft_same_type(input, i), WORD);
}

t_lex	*ft_lexer(char *input)
{
	int		i;
	t_lex	*lexer;

	lexer = NULL;
	i = 0;
	if (!input)
		return (NULL);
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (input[i] == '\0')
		return (NULL);
	while (input && input[i])
	{
		ft_inside_lexer(input, &i, &lexer);
		i++;
	}
	lexer = ft_set_state(lexer);
	return (lexer);
}
