/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excutions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:47:14 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/13 14:08:16 by yichiba          ###   ########.fr       */
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


void		_execution1(t_global *global,int i,t_pars *tmp)
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
void	_execution2(t_std *std,int output,t_pars *tmp,t_global *global)
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

void	_execution(t_global *global, t_pars *tmp, int i)
{
	int	output;
	t_std	std;

	if (tmp->next)
		pipe(global->fd);
	global->pids[i] = fork();
	if (global->pids[i] == 0)
	{
		_execution1(global,i,tmp);
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
t_env *parted(t_pars *parser, t_env *env, t_global global, t_std std)
{
	t_pars *tmp;
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
	t_std 		std;

	if (!parser)
		return (env);
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
