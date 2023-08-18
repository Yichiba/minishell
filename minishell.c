/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:13:38 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/17 18:39:57 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_full_cmd(t_lex *start, int args)
{
	char	**cmd;
	int		i;
	t_lex	*tmp;

	cmd = NULL;
	i = 0;
	tmp = start;
	if (!tmp)
		return (NULL);
	cmd = ft_calloc((args + 1), sizeof(char *));
	while (tmp && tmp->type != PIPE)
	{
		if (tmp_isredir(tmp))
		{
			tmp = tmp->next->next;
			continue ;
		}
		cmd[i++] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

int	count_pipes(t_lex *lexer)
{
	int	i;

	i = 0;
	while (lexer)
	{
		if (lexer->type == PIPE)
			i++;
		lexer = lexer->next;
	}
	return (i + 1);
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (g_glob.g_state == 1)
			close(0);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

t_env	*ft_minishell(t_env *env, int std_in)
{
	char	*input;
	t_lex	*lexer;
	t_pars	*parser;

	while (1)
	{
		dup2(std_in, 0);
		input = readline("\e[1;53mMiniShell$ \e[0m");
		add_history(input);
		if (input == NULL)
			exit(g_glob.g_exit);
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		input = ft_syntax_quot(input);
		lexer = ft_lexer(input);
		lexer = ft_clean(lexer, env);
		parser = ft_parser(lexer);
		env = ft_excutions(parser, env);
		if (parser && parser->args_num == 0 && !parser->red)
			lexer = NULL;
		ft_free(lexer, parser, &input);
	}
}

int	main(int ac, char **av, char **environ)
{
	t_lex	*lexer;
	t_pars	*parser;
	t_env	*env;
	int		std_in;

	(void)ac;
	(void)av;
	g_glob.g_exit = 0;
	lexer = NULL;
	parser = NULL;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	env = get_env(environ);
	std_in = dup(0);
	env = ft_minishell(env, std_in);
	return (g_glob.g_exit);
}
