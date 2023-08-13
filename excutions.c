/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excutions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majrou <majrou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:47:14 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/13 15:43:30 by majrou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_execution(t_global *global, t_pars *tmp, int i)
{
	int		output;
	t_std	std;

	if (tmp->next)
		pipe(global->fd);
	global->pids[i] = fork();
	if (global->pids[i] == 0)
	{
		_execution1(global, i, tmp);
		output = ft_redirections(tmp, &global->fide, &std);
		_execution2(&std, output, tmp, global);
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

t_env	*parted(t_pars *parser, t_env *env, t_global global, t_std std)
{
	t_pars	*tmp;
	int		i;

	tmp = parser;
	i = 0;
	if (tmp->args_num && ft_is_builtins(tmp->full_cmd[0]) && !tmp->next)
	{
		ft_redirections(tmp, &global.fide, &std);
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
	return (NULL);
}

t_env	*ft_excutions(t_pars *parser, t_env *env)
{
	t_global	global;
	t_env		*tmp;
	t_std		std;

	if (!parser)
		return (env);
	parser = ft_herdoc_intiat(parser);
	initialisation(&global, parser);
	global.env = env;
	std.file_in = -1;
	std.file_out = -1;
	tmp = parted(parser, env, global, std);
	if (tmp)
		return (tmp);
	if (parser)
		ft_wait(global, parser);
	if (ft_count_cmd(parser) > 1 || (parser->args_num
			&& !ft_is_builtins(parser->full_cmd[0])))
		ft_free_global(&global, parser);
	return (env);
}
