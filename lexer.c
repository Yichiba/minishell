/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:57:51 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/06 14:13:48 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lex	*ft_set_state(t_lex *lexer)
{
	t_lex	*tmp;

	tmp = lexer;
	while (tmp && tmp->next)
	{
		if (tmp->type == DOUBLE_QUOTE)
		{
			tmp = tmp->next;
			while (tmp && tmp->next && tmp->type != DOUBLE_QUOTE)
			{
				tmp->state = IN_DQUOTE;
				if (tmp->type != VAR)
					tmp->type = WORD;
				tmp = tmp->next;
			}
		}
		else if (tmp->type == QUOTE)
		{
			tmp = tmp->next;
			while (tmp && tmp->next && tmp->type != QUOTE)
			{
				tmp->state = IN_QUOTE;
				tmp->type = WORD;
				tmp = tmp->next;
			}
		}
		else
			tmp->state = GENERAL;
		tmp = tmp->next;
	}
	return (lexer);
}

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

char	*ft_same_type(char *input, int *i)
{
	char	*str;
	int		j;

	j = 0;
	while (input[*i + j] != ' ' && input[*i + j] != '\0' && input[*i
		+ j] != '\'' && input[*i + j] != '\"' && input[*i + j] != '$'
		&& input[*i + j] != '|' && input[*i + j] != '<' && input[*i + j] != '>')
		j++;
	str = ft_calloc(j + 1, sizeof(char));
	j = 0;
	while (input[*i] != ' ' && input[*i] != '\0' && input[*i] != '\''
		&& input[*i] != '\"' && input[*i] != '$' && input[*i] != '|'
		&& input[*i] != '<' && input[*i] != '>')
		str[j++] = input[(*i)++];
	str[j] = '\0';
	(*i)--;
	return (str);
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

t_lex	*ft_lexer(char *input)
{
	int i;
	t_lex *lexer = NULL;
	

	i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
			lexer = ft_add(lexer, ft_strdup(" "), WHITE_SPACE);
		else if (input[i] == '\'')
			lexer = ft_add(lexer, ft_strdup("\'"), QUOTE);
		else if (input[i] == '\"')
			lexer = ft_add(lexer, ft_strdup("\""), DOUBLE_QUOTE);
		else if (input[i] == '$')
 				lexer = ft_add(lexer, ft_dollar(input, &i), VAR);
		else if (input[i] == '|')
			lexer = ft_add(lexer, ft_strdup("|"), PIPE);
		else if (input[i + 1] && input[i] == '<' && input[i + 1] == '<' && i++)
			lexer = ft_add(lexer, ft_strdup("<<"), HERE_DOC);
		else if (input[i] == '<')
			lexer = ft_add(lexer, ft_strdup("<"), REDIR_IN);
		else if (input[i + 1] && input[i] == '>' && input[i + 1] == '>' && i++)
			lexer = ft_add(lexer, ft_strdup(">>"), DREDIR_OUT);
		else if (input[i] == '>')
			lexer = ft_add(lexer, ft_strdup(">"), REDIR_OUT);
		else
			lexer = ft_add(lexer, ft_same_type(input, &i), WORD);
		i++;
	}
	lexer = ft_set_state(lexer);	
	return (lexer);
}
