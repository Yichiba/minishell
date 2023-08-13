/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 11:32:58 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/12 20:47:14 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_minishell(t_env *env)
{
	char	*input;
	t_lex	*lexer;
	t_pars	*parser;

	while (1)
		input = readline("\e[1;53mMiniShell$ \e[0m");
}

void	sig_handler(int sig)
{
	if(sig == SIGINT)
	{
		printf("SIGINT\n");
	}
	else if(sig == SIGQUIT)
		return ;
}

int	main(int ac, char **av, char **environ)
{
	t_env	*env;

	while (1)
	{
		signal(SIGINT , sig_handler);
		signal(SIGINT , sig_handler);
		signal(SIGQUIT , sig_handler);
		env = ft_minishell(env);
	}
	return (g_exit);
}
