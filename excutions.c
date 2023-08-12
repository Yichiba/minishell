/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excutions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:47:14 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/12 17:45:07 by yichiba          ###   ########.fr       */
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

void	_execution(t_global *global, t_pars *tmp, int i)
{
	if (tmp->next)
		pipe(global->fd);
	global->pids[i] = fork();
	if (global->pids[i] == 0)
	{
		// if (tmp->red)
		// 	global->fide.file = ft_redirections(tmp->red, &global->fide);
		if (global->fide.file == -5)
			exit(1);
		ft_pipe(global, i, global->id, tmp);
	}
	if (i > 0)
		close(global->id);
	if (tmp->next)
	{
		global->id = global->fd[0];
		close(global->fd[1]);
	}
	if (tmp->red)
		close_file(tmp->red, &global->fide);
}

int	ft_count_cmd(t_pars *parser)
{
	int		i;
	t_pars	*tmp;

	i = 0;
	tmp = parser;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	initialisation(t_global *global, t_pars *parser)
{
	if (!parser)
		return ;
	global->fide.file = -1;
	global->fide.std_in = -1;
	global->fide.std_out = -1;
	global->id = -1;
	if (ft_count_cmd(parser) > 1 || (parser->args_num
			&& !ft_is_builtins(parser->full_cmd[0])))
		global->pids = malloc(sizeof(int) * (ft_count_cmd(parser)));
}

t_env	*ft_excutions(t_pars *parser, t_env *env)
{
	t_global	global;
	t_pars		*tmp;
	int			i;

	i = 0;
	if (!parser)
		return (env);
	tmp = parser;
	initialisation(&global, parser);
	global.env = env;
	if (tmp->args_num && ft_is_builtins(tmp->full_cmd[0]) && !tmp->next)
	{
		if (tmp->red)
			global.fide.file = ft_redirections(tmp->red, &global.fide);
		env = ft_builtins(tmp, env);
		if (tmp->red)
			close_file(tmp->red, &global.fide);
		return (env);
	}
	else
	{
		while (tmp)
		{
			if (!tmp || tmp->args_num == 0)
				return (env);
			else
				_execution(&global, tmp, i);
			tmp = ((i++), tmp->next);
		}
	}
	if (parser)
		ft_wait(global, parser);
	if (ft_count_cmd(parser) > 1 || (parser->args_num
			&& !ft_is_builtins(parser->full_cmd[0])))
		ft_free_global(&global, parser);
	return (env);
}
