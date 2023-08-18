/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 10:39:33 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/17 16:06:07 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tmp_isredir(t_lex *tmp)
{
	if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT
		|| tmp->type == DREDIR_OUT || tmp->type == HERE_DOC)
		return (1);
	return (0);
}

t_lex	*ft_syntax_pipe(t_lex *lexer)
{
	t_lex	*tmp;
	int		i;

	i = 0;
	tmp = lexer;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (!tmp->next || i == 0 || (tmp->next->type != WORD
					&& !tmp_isredir(tmp->next)))
			{
				printf("minishell: syntax error\n");
				ft_free_lex(lexer);
				return (NULL);
			}
		}
		i++;
		tmp = tmp->next;
	}
	return (lexer);
}

t_lex	*ft_syntax_redir(t_lex *lexer)
{
	t_lex	*tmp;

	tmp = lexer;
	while (tmp)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT
			|| tmp->type == DREDIR_OUT || tmp->type == HERE_DOC)
		{
			if (!tmp->next || (tmp->next->type != VAR
					&& tmp->next->type != WORD))
			{
				printf("minishell: syntax error\n");
				ft_free_lex(lexer);
				return (NULL);
			}
		}
		tmp = tmp->next;
	}
	return (lexer);
}

char	*ft_same_type(char *input, int *i)
{
	char	*str;
	int		j;

	j = 0;
	while (input[*i + j] != ' ' && input[*i + j] != '\0'
		&& input[*i + j] != '\'' && input[*i + j] != '\"'
		&& input[*i + j] != '$' && input[*i + j] != '|'
		&& input[*i + j] != '<' && input[*i + j] != '>')
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

t_lex	*ft_syntax(t_lex *lexer)
{
	lexer = ft_syntax_pipe(lexer);
	lexer = ft_syntax_redir(lexer);
	if (!lexer)
		g_glob.g_exit = 2;
	return (lexer);
}
