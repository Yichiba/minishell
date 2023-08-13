/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majrou <majrou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:14:06 by majrou            #+#    #+#             */
/*   Updated: 2023/08/13 15:25:01 by majrou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait(t_global global, t_pars *parser)
{
	int		status;
	t_pars	*tmp;
	int		i;

	tmp = parser;
	i = 0;
	while (tmp)
	{
		waitpid(global.pids[i], &status, 0);
		i++;
		tmp = tmp->next;
	}
	g_exit = status >> 8;
}

void	_execution1(t_global *global, int i, t_pars *tmp)
{
	if (global->fide.file == -5)
		exit(1);
	if (i > 0)
	{
		dup2(global->id, 0);
		close(global->id);
	}
	if (tmp->next)
	{
		dup2(global->fd[1], 1);
		close(global->fd[1]);
		close(global->fd[0]);
	}
}

void	_execution2(t_std *std, int output, t_pars *tmp, t_global *global)
{
	if (std->file_in != -1)
		dup2(std->file_in, 0);
	if (std->file_out != -1)
		dup2(std->file_out, 1);
	if (output == 1)
		exit (1);
	if (ft_is_builtins(tmp->full_cmd[0]))
	{
		ft_builtins(tmp, global->env);
		exit(0);
	}
	else
		find_commands(global->env, tmp);
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
