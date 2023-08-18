/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 21:47:54 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/17 14:54:21 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_else(t_lex *tmp, t_env *env)
{
	char	*var_name;
	char	*var_value;

	var_name = ft_strdup(tmp->content + 1);
	free(tmp->content);
	var_value = ft_strdup(look_for_var(env, var_name));
	var_value = ft_trim(var_value, ' ');
	var_value = ft_trim(var_value, '	');
	tmp->content = var_value;
	tmp->type = WORD;
}

void	ft_tmp_state(t_lex *tmp, t_env *env)
{
	char	*var_name;
	char	*var_value;

	var_name = ft_strdup(tmp->content +1);
	free(tmp->content);
	var_value = ft_strdup(look_for_var(env, var_name));
	tmp->content = var_value;
	tmp->type = WORD;
}

void	ft_tmp_content(t_lex *tmp, t_env *env)
{
	(void)env;
	free(tmp->content);
	tmp->content = ft_strdup("$");
	tmp->type = WORD;
}

t_lex	*ft_expand_variables(t_lex *lexer, t_env *env)
{
	t_lex	*tmp;

	tmp = lexer;
	while (tmp)
	{
		if (tmp->type == VAR)
		{
			if (ft_strcmp(tmp->content, "$") == 1)
				ft_tmp_content(tmp, env);
			else if (ft_strcmp(tmp->content, "$?") == 1)
			{
				free(tmp->content);
				tmp->content = ft_itoa(g_glob.g_exit);
				tmp->type = WORD;
			}
			else if (tmp->content[0] == '\0')
				tmp->type = WORD;
			else if (tmp->state == IN_DQUOTE)
				ft_tmp_state(tmp, env);
			else
				ft_else(tmp, env);
		}
		tmp = tmp->next;
	}
	return (lexer);
}
