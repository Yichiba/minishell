/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_outils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:10:17 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/07 22:22:48 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lex	*ft_remove_quote(t_lex *lexer)
{
	t_lex *tmp;
	t_lex *tmp2;
	tmp = lexer;
	while(tmp)
	{
		tmp2 = tmp->next;
		if(tmp->type == QUOTE || tmp->type == DOUBLE_QUOTE )
			lexer = remove_node(lexer,tmp);
			tmp = tmp2;
	}
	tmp = lexer;
	while(tmp && tmp->next)
	{
		if((tmp->type == WORD && tmp->state == GENERAL ) && (tmp->next->type == WORD && tmp->next->state == GENERAL))
			{
				tmp->content = ft_strjoin(tmp->content, tmp->next->content);
				lexer = remove_node(lexer,tmp->next);
				tmp = lexer;
			}
		else if((tmp->type == WORD && tmp->state == IN_DQUOTE ) && (tmp->next->type == WORD && tmp->next->state == IN_DQUOTE))
			{
				tmp->content = ft_strjoin(tmp->content, tmp->next->content);
				lexer = remove_node(lexer,tmp->next);
				tmp = lexer;
			}
		tmp = tmp->next;
	}
	return(lexer);
}


t_lex *remove_node(t_lex *lex, t_lex *node) 
{
    if (lex == node) 
	{
        t_lex *next_node = lex->next;
        free(lex->content);
        free(lex);
		lex = NULL;
        return next_node;
    }
    t_lex *tmp = lex;
    while (tmp && tmp->next != node)
		tmp = tmp->next;
	t_lex * next_node = NULL;
    if (tmp)
	{
		if(tmp->next->next)
        	next_node = tmp->next->next;
        free(tmp->next->content);
        free(tmp->next);
        tmp->next = next_node;
    }
	
    return lex;
}

t_lex *ft_remove_space(t_lex *lexer)
{
    t_lex *tmp = lexer;
    t_lex *prev = NULL;
	
    while (tmp) 
	{
        if (tmp->type == WHITE_SPACE) 
		{
            t_lex *to_remove = tmp;
            tmp = tmp->next;
            if (prev) 
			 prev->next = tmp;
            else
                lexer = tmp; 
            free(to_remove->content);
            free(to_remove);
		}
        else 
		{
            prev = tmp;
            tmp = tmp->next;
        }
    }
    return lexer;
}

char *look_for_var(t_env *env,char *var_name)
{
	t_env *tmp;
	tmp = env;
	while(tmp)
	{
		if(ft_strcmp(var_name,tmp->var) == 1)
			{
				free(var_name);
				return(tmp->str);
			}
		tmp = tmp->next;
	}
	free(var_name);
	return(ft_strdup(""));
}

t_lex	*ft_expand_variables(t_lex	*lexer,t_env	*env)
{
	t_lex	*tmp;
	char *var_name;
	char *var_value;
	tmp	= lexer;
	while(tmp)
	{
		if(tmp->type == VAR)
			{
				if (ft_strcmp(tmp->content, "$") == 1)
				{
					free(tmp->content);
					tmp->content = ft_strdup("$");
					tmp->type = WORD;
				}
				else if (ft_strcmp(tmp->content, "$?") == 1)
				{
					free(tmp->content);
					tmp->content = ft_itoa(g_exit);
					tmp->type = WORD;
				}
				else if(tmp->state == IN_DQUOTE)
				{
					var_name = ft_strdup(tmp->content +1);
					free(tmp->content);
					var_value = look_for_var(env,var_name);
					tmp->content = var_value;
					tmp->type = WORD;
				}
				else 
				{
					//Different output in tes echo $@1; echo "$@1"
					var_name = ft_strdup(tmp->content +1);
					free(tmp->content);
					var_value = ft_trim(look_for_var(env,var_name));
					tmp->content = var_value;
					tmp->type = WORD;
				}
			}
		tmp = tmp->next;
	}
	return(lexer);
}

t_lex *ft_clean(t_lex *lexer,t_env *env)
{
	t_lex *tmp;
	lexer = ft_expand_variables(lexer,env);
	lexer = ft_remove_quote(lexer);
	tmp  = lexer;
	while(tmp && tmp->next)
	{
		
		if(tmp->type == VAR && tmp->next->type == WORD)
				tmp->content = ft_strjoin(tmp->content, tmp->next->content);	
		else if(tmp->state == IN_QUOTE && tmp->next->state == IN_QUOTE)
				tmp->content = ft_strjoin(tmp->content, tmp->next->content);
		else if(tmp->state == IN_DQUOTE && tmp->type != VAR && tmp->next->type != VAR && tmp->next->state == IN_DQUOTE ) //watch out  ,i removed lexer = remove_node(lexer, tmp->next);from all conditions
				tmp->content = ft_strjoin(tmp->content, tmp->next->content);	
		else if(tmp->type == WORD && tmp->next->type == WORD)
				tmp->content = ft_strjoin(tmp->content, tmp->next->content);
		lexer = remove_node(lexer, tmp->next);	
		// else
			tmp = tmp->next;
	}
	lexer = ft_remove_space(lexer);
	lexer = ft_syntax(lexer);
	return(lexer);
}
