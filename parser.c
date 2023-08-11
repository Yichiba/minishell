/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:17:12 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/11 10:09:14 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_count_args(t_lex *start)
{
	int i = 0;
	t_lex *tmp;
	tmp = start;
	while(tmp && tmp->type != PIPE)
	{
		if((tmp->type == HERE_DOC || tmp->type == REDIR_IN || tmp->type == REDIR_OUT || tmp->type == DREDIR_OUT) && tmp->next)
			i = i - 2;
		i++;
		tmp = tmp->next;
	}
	return(i);
}

t_pars *ft_lstadd_back(t_pars **lst, t_pars *new)
{
    t_pars *d;

    d = *lst;
    if (!d)
        *lst = new;
    else
    {
        while (d->next != NULL)
            d = d->next;
        d->next = new;
    }
    return (new); 
}

t_pars	*add_new_node(t_lex *start,int args)
{
		t_pars *parser = NULL;
		t_lex *start1;
		parser = ft_calloc(sizeof(t_pars), 1);
		parser->full_cmd = NULL;
		parser->red = ft_red(start,&start1);
		if(args)
			parser->full_cmd = get_full_cmd(start1, args);
		parser->args_num = args;
		parser->next = NULL;
		return(parser);
}

t_pars *ft_parser(t_lex *lexer)
{
	t_lex	*start;
	t_pars	*new;
	t_pars	*head;
	t_lex	*ptr;
	
	start = lexer;
	ptr = lexer;
	head = NULL;
	while (ptr)
	{
		if(ptr->type == PIPE)
		{
			new = add_new_node(start,ft_count_args(start));
			ft_lstadd_back(&head,new);
			if(!ptr->next)
				return(head) ;
			start = ptr->next;
		}
		if(!ptr->next)
		{
			new = add_new_node(start,ft_count_args(start));
			ft_lstadd_back(&head,new);
				return(head);
		}
		ptr = ptr->next;
	}
	
	return(head);
}


