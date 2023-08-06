/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 19:23:22 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/04 19:58:55 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_func(t_pars *tmp,t_env *env,int *fd,int *pids,int input,int stdin,int stdout,int file,int i)
{
	while (tmp)
	{
		if (!tmp)
			return (env);
		if (tmp->args_num == 0)
			return (env);
		if (tmp->red)
			file = ft_redirections(tmp->red, &stdin, &stdout);
		// ft_builtins(tmp, env)
		if (ft_strcmp(tmp->full_cmd[0], "export") == 1)
			env = ft_export(env, tmp->full_cmd);
		else if (ft_strcmp(tmp->full_cmd[0], "unset") == 1)///////// mainprocess
			env = ft_unset(env, tmp->full_cmd);
		else if (ft_strcmp(tmp->full_cmd[0], "cd") == 1) ///////
			env = ft_cd(env, tmp->full_cmd);
		else if (ft_strcmp(tmp->full_cmd[0], "pwd") == 1)
			env = ft_pwd(env);
		else if (ft_strcmp(tmp->full_cmd[0], "echo") == 1)
			ft_echo(tmp->full_cmd);
		else if (ft_strcmp(tmp->full_cmd[0], "env") == 1)
			ft_env(env);
		else if (ft_strcmp(tmp->full_cmd[0], "exit") == 1) ////////
			env = ft_exit(env, tmp->full_cmd);
		else
		{
			if (tmp->next)
				pipe(fd);
			pids[i] = fork();
			if (pids[i] == 0)
			{
				if (i > 0)
				{
					dup2(input, 0);
					close (input);
				}
				if (tmp->next)
				{
					dup2(fd[1], 1);
					close (fd[1]);
					close (fd[0]);
				}
				find_commands(env, tmp);
			}
			
			if (i > 0)
				close (input);
			if (tmp->next)
			{
				input = fd[0];
				close (fd[1]);
			}
		}
		if (tmp->red)
			close_file(file, tmp->red, &stdin, &stdout);
		i++;
		tmp = tmp->next;
	}
}