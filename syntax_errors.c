/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 10:39:33 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/10 17:01:32 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int tmp_isredir(t_lex *tmp)
{
    if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT || tmp->type == DREDIR_OUT || tmp->type == HERE_DOC)
        return (1);
    return (0);
}

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
    if(tmp && tmp->type == PIPE)
    {
        printf("minishell: syntax error\n");
        return (NULL);
    }
    while (tmp)
    {
        if (tmp->type == PIPE)
        {
            if (!tmp->next )
            {
                printf("minishell: syntax error\n");
                ft_free_lex(lexer);
                return (NULL);
            }
            if (!tmp->next &&  tmp->next->type != WORD && !tmp_isredir(tmp->next) )
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
t_lex   *ft_syntax_redir(t_lex *lexer)
{
    t_lex	*tmp;
    tmp = lexer;
    while (tmp)
    {
        if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT || tmp->type == DREDIR_OUT || tmp->type == HERE_DOC)
        {
            if (!tmp->next)
            {
                printf("minishell: syntax error\n");
                ft_free_lex(lexer);
                return(NULL);
            }
            if (tmp->next->type != VAR && tmp->next->type != WORD)
            {
                printf("minishell: syntax error\n");
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
                printf("minishell: syntax error\n");
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
    if(!lexer)
        g_exit = 2;
	return (lexer);
}