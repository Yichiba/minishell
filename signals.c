/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 11:32:58 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/12 14:24:53 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



t_env	*ft_minishell(t_env *env)
{
	char	*input;
	t_lex	*lexer;
	t_pars	*parser;
    

	while (1)
	{
		input = readline("\e[1;53mMiniShell$ \e[0m");
	}
}

int	main(int ac, char **av, char **environ)
{
    t_env	*env;
	while (1)
	{
        signal(SIGINT, ft_ctrl_c);
        signal(SIGQUIT, ft_ctrl_slash);
        signal(SIGTERM, ft_ctrl_d);
		env = ft_minishell(env);
		// system("leaks minishell");
	}
	return (g_exit);
}