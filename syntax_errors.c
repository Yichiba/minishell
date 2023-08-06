/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 10:39:33 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/06 14:18:32 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void    ft_free_lex(t_lex *lexer)
{
    t_lex   *tmp;

    while (lexer)
    {
        tmp = lexer;
        lexer = lexer->next;
        free(tmp->content);
        free(tmp);
    }
}

t_lex	*ft_syntax_pipe(t_lex *lexer)
{
    t_lex	*tmp;

    tmp = lexer;
    if(tmp->type == PIPE)
    {
        printf("syntax error near unexpected token `|'\n");
        g_exit = 258;
        return (NULL);
    }
    while (tmp)
    {
        if (tmp->type == PIPE)
        {
            if (tmp->next == NULL || tmp->next->type == PIPE || tmp->next->type != WORD )
            {
                printf("syntax error near unexpected token `|'\n");
                g_exit = 258;
                ft_free_lex(lexer);
                return (NULL);
            }
        }
        tmp = tmp->next;
    }
    return (lexer);
}
t_lex   *ft_syntax_redir(t_lex *lexer)
{
    t_lex	*tmp;
    tmp = lexer;
    while (tmp)
    {
        if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT || tmp->type == DREDIR_OUT || tmp->type == HERE_DOC)
        {
            if (tmp->next == NULL || (tmp->next->type != VAR && tmp->next->type != WORD))
            {
                printf("tmp->next->type = %s\n", get_type(tmp->next->type));
                printf("syntax error near unexpected token `newline'\n");
                g_exit = 258;
                ft_free_lex(lexer);
                return(NULL);
            }
        }
        tmp = tmp->next;
    }
    return (lexer);
}
t_lex	*ft_syntax_quote(t_lex *lexer)
{
    t_lex	*tmp;

    char *quote;
    tmp = lexer;
    while (tmp)
    {
        if (tmp->type == QUOTE || tmp->type == DOUBLE_QUOTE)
        {
            quote = tmp->content;
            tmp = tmp->next;
            while(tmp)
            {
                if (tmp->content == quote)
                    break;
                tmp = tmp->next;
            }
            if (tmp== NULL)
            {
                printf("syntax error near unexpected token `'\n");
                g_exit = 258;
                ft_free_lex(lexer);
                return(NULL);
            }
        }
        if(tmp == NULL)
            break;
        tmp = tmp->next;
    }
    return (lexer);
}

t_lex	*ft_syntax(t_lex *lexer)
{
	lexer = ft_syntax_pipe(lexer);
	lexer = ft_syntax_redir(lexer);
	lexer = ft_syntax_quote(lexer);
	return (lexer);
}