/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:14:06 by majrou            #+#    #+#             */
/*   Updated: 2023/08/17 12:44:13 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait(t_g_global g_global, t_pars *parser)
{
	int		status;
	t_pars	*tmp;
	int		i;

	tmp = parser;
	i = 0;
	while (tmp)
	{
		waitpid(g_global.pids[i], &status, 0);
		i++;
		tmp = tmp->next;
	}
	g_glob.g_exit = status >> 8;
}

void	_execution1(t_g_global *g_global, int i, t_pars *tmp)
{
	if (g_global->fide.file == -5)
		exit(1);
	if (i > 0)
	{
		dup2(g_global->id, 0);
		close(g_global->id);
	}
	if (tmp->next)
	{
		dup2(g_global->fd[1], 1);
		close(g_global->fd[1]);
		close(g_global->fd[0]);
	}
}

void	_execution2(t_std *std, int output, t_pars *tmp, t_g_global *g_global)
{
	if (std->file_in != -1)
		dup2(std->file_in, 0);
	if (std->file_out != -1)
		dup2(std->file_out, 1);
	if (output == 1)
		exit (1);
	if (ft_is_builtins(tmp->full_cmd[0]))
	{
		ft_builtins(tmp, g_global->env);
		exit(0);
	}
	else
		find_commands(g_global->env, tmp);
}

t_pars	*ft_herdoc_intiat(t_pars *parser)
{
	t_pars	*tmp;
	t_red	*tmp_red;

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
	return (parser);
}

char	*ft_syntax_quot(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input && input[i])
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
				write(2, "minishell: unexpected EOF looking for matching\n", 47);
				g_glob.g_exit = 2;
				return (NULL);
			}
		}
		i++;
	}
	return (input);
}
