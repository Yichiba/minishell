/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:17:12 by yichiba           #+#    #+#             */
/*   Updated: 2023/07/25 18:56:15 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_syntax_pipe(t_lex * lexer)
 {
	 t_lex *tmp;
	 tmp = lexer;
	 if(tmp->type == PIPE )
	 	return(0);
	 while(tmp && tmp->next)
	 {
		 if(tmp->type == PIPE)
		 {
			 if(tmp->next->type != WORD )
				return(0);
		 }
		 tmp = tmp->next;
	 }
	 
	 if(tmp->type == PIPE)
	 	return(0);
	 return(1);
 }
int ft_count_args(t_lex *start)
{
	int i = 0;
	t_lex *tmp;
	tmp = start;
	while(tmp && tmp->type != PIPE)
	{
		if(tmp->type == HERE_DOC || tmp->type == REDIR_IN || tmp->type == REDIR_OUT || tmp->type == DREDIR_OUT)
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
		t_pars *parser ;
		parser = malloc(sizeof(t_pars));
		parser->red = ft_red(start);
		parser->full_cmd = get_full_cmd(start, args);
		parser->args_num = args;
		parser->next = NULL;
		return(parser);
}

t_pars *ft_parser(t_lex *lexer)
{
	t_lex	*start;
	t_pars	*head;
	t_lex	*ptr;

	
	start = lexer;
	ptr = lexer;
	head = NULL;
	while (ptr)
	{
		if(!ptr->next || ptr->type == PIPE)
		{
			ft_lstadd_back(&head,add_new_node(start,ft_count_args(start)));
			if(ptr->next != NULL)
				start = ptr->next;
		}
		ptr = ptr->next;
	}
	
	return(head);
}


