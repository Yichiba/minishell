/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excutions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:47:14 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/17 18:36:13 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_execution(t_g_global *g_global, t_pars *tmp, int i)
{
	int		output;
	t_std	std;

	if (tmp->next)
		pipe(g_global->fd);
	g_global->pids[i] = fork();
	if (g_global->pids[i] == 0)
	{
		_execution1(g_global, i, tmp);
		output = ft_redirections(tmp, &g_global->fide, &std);
		_execution2(&std, output, tmp, g_global);
	}
	if (i > 0)
		close(g_global->id);
	if (tmp->next)
	{
		g_global->id = g_global->fd[0];
		close(g_global->fd[1]);
	}
	if (tmp->red)
		close_file(tmp->red, &g_global->fide);
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

void	initialisation(t_g_global *g_global, t_pars *parser)
{
	if (!parser)
		return ;
	g_global->fide.file = -1;
	g_global->fide.std_in = -1;
	g_global->fide.std_out = -1;
	g_global->id = -1;
	if (ft_count_cmd(parser) > 1 || (parser->args_num
			&& !ft_is_builtins(parser->full_cmd[0])))
		g_global->pids = malloc(sizeof(int) * (ft_count_cmd(parser)));
}

t_env	*parted(t_pars *tmp, t_env *env, t_g_global g_global, t_std std)
{
	g_global.fide.i = 0;
	if (tmp->args_num && ft_is_builtins(tmp->full_cmd[0]) && !tmp->next)
	{
		ft_redirections(tmp, &g_global.fide, &std);
		if (std.file_in == -5)
			return (env);
		env = ft_builtins(tmp, env);
		if (tmp->red)
			close_file(tmp->red, &g_global.fide);
		return (env);
	}
	else
	{
		while (tmp)
		{
			ft_redirections(tmp, &g_global.fide, &std);
			if (!tmp || tmp->args_num == 0 || std.file_in == -5)
				return (g_global.env);
			else
				_execution(&g_global, tmp, g_global.fide.i);
			tmp = ((g_global.fide.i++), tmp->next);
		}
	}
	return (NULL);
}

t_env	*ft_excutions(t_pars *parser, t_env *env)
{
	t_g_global	g_global;
	t_env		*tmp;
	t_std		std;

	if (!parser)
		return (env);
	parser = ft_herdoc_intiat(parser);
	initialisation(&g_global, parser);
	g_global.env = env;
	std.file_in = -1;
	std.file_out = -1;
	tmp = parted(parser, env, g_global, std);
	if (tmp)
		return (tmp);
	if (parser)
		ft_wait(g_global, parser);
	if (ft_count_cmd(parser) > 1 || (parser->args_num
			&& !ft_is_builtins(parser->full_cmd[0])))
		ft_free_g_global(&g_global, parser);
	return (env);
}
