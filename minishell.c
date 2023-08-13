/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:13:38 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/13 10:23:05 by yichiba          ###   ########.fr       */
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

char	*ft_syntax_quot(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote = input[i++];
			while (input[i])
			{
				if (input[i] == quote)
					break ;
				i++;
			}
			if (input[i] == '\0')
			{
				write(2, "minishell: unexpected EOF while looking for matching\n", 53);
				g_exit = 2;
				return (NULL);
			}
		}
		i++;
	}
	return (input);
}

t_env	*ft_minishell(t_env *env)
{
	char	*input;
	t_lex	*lexer;
	t_pars	*parser;
	t_pars	*tmp;
	t_red	*tmp_red;

	while (1)
	{
		input = readline("\e[1;53mMiniShell$ \e[0m");
		add_history(input);
		if (input == NULL)
			exit(g_exit);
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		input = ft_syntax_quot(input);
		lexer = ft_lexer(input);
		lexer = ft_clean(lexer, env);
		parser = ft_parser(lexer);

		tmp = parser;
		while (tmp)
		{
			tmp_red = tmp->red;
			tmp->here_doc = -1;
			while (tmp_red)
			{
				if (tmp->here_doc != -1)
					close (tmp->here_doc);
				if (tmp_red->type == HERE_DOC)
					tmp->here_doc = ft_open_herdoc(tmp_red->file);
				tmp_red = tmp_red->next;
			}
			tmp = tmp->next;
		}
		
		env = ft_excutions(parser, env);
		if (parser && parser->args_num == 0)
			lexer = NULL;
		ft_free(lexer, parser);
		free(input);
	}
}

int	main(int ac, char **av, char **environ)
{
	t_lex	*lexer;
	t_pars	*parser;
	t_env	*env;

	(void)ac;
	(void)av;
	g_exit = 0;
	lexer = NULL;
	parser = NULL;
	env = get_env(environ);
	while (1)
	{
		env = ft_minishell(env);
		system("leaks minishell");
	}
	return (g_exit);
}
