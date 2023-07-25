/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_outils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:10:17 by yichiba           #+#    #+#             */
/*   Updated: 2023/07/25 20:28:45 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lex *ft_join(t_lex *tmp, t_lex *next)
{
	char *str;
	char *tab;
	str = ft_strdup(tmp->content);
	tab = ft_strdup(next->content);
	tmp->content = ft_strjoin(str, tab);
	free(str);
	free(tab);
	return(tmp);
}


t_lex	*ft_remove_quote(t_lex *lexer)
{
	t_lex *tmp;
	tmp = lexer;
	while(tmp)
	{
		if(tmp->type == QUOTE || tmp->type == DOUBLE_QUOTE )
			lexer = remove_node(lexer,tmp);
			tmp = tmp->next;
	}
	tmp = lexer;
	while(tmp && tmp->next)
	{
		if((tmp->type == WORD && tmp->state == GENERAL ) && (tmp->next->type == WORD && tmp->next->state == GENERAL))
			{
				tmp = ft_join(tmp,tmp->next);
				lexer = remove_node(lexer,tmp->next);
			}
		tmp = tmp->next;
	}
	return(lexer);
}

t_lex *remove_node(t_lex *lex, t_lex *node) {
    if (lex == node) {
        t_lex *next_node = lex->next;
        free(lex->content);
        free(lex);
        return next_node;
    }
    t_lex *tmp = lex;
    while (tmp && tmp->next != node)
		tmp = tmp->next;
    if (tmp)
	{
        t_lex *next_node = tmp->next->next;
        free(tmp->next->content);
        // free(tmp->next);
        tmp->next = next_node;
    }

    return lex;
}

t_lex *ft_remove_space(t_lex *lexer) {
    t_lex *tmp = lexer;
    t_lex *prev = NULL;
    while (tmp) {
        if (tmp->type == WHITE_SPACE) {
            t_lex *to_remove = tmp;
            tmp = tmp->next;
            if (prev) {
                prev->next = tmp;
            } else {
                lexer = tmp; 
            }
            free(to_remove->content);
            free(to_remove);
        } else {
            prev = tmp;
            tmp = tmp->next;
        }
    }
    return lexer;
}

t_lex *ft_clean(t_lex *lexer)
{
	t_lex *tmp;
	tmp  = lexer;
	lexer = ft_remove_quote(lexer);
	while(tmp && tmp->next)
	{
		if(tmp->state == IN_QUOTE && tmp->next->state == IN_QUOTE)
			{
				ft_join(tmp, tmp->next);
				lexer = remove_node(lexer, tmp->next);
			}
		else if(tmp->state == IN_DQUOTE && tmp->type != VAR && tmp->next->type != VAR && tmp->next->state == IN_DQUOTE )
			{
				ft_join(tmp, tmp->next);
				lexer = remove_node(lexer, tmp->next);
			}	
		else if(tmp->type == WORD && tmp->next->type == WORD)
			{
				ft_join(tmp, tmp->next);
				lexer = remove_node(lexer, tmp->next);
			}	
		else
			tmp = tmp->next;
	}
	lexer = ft_remove_space(lexer);
	return(lexer);
}