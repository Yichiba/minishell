/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 12:58:55 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/04 16:00:42 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_file(int file, t_red *red, int *stdin, int *stdout)
{
	if (red->type == REDIR_OUT || red->type == DREDIR_OUT)
	{
		close(file);
		dup2(*stdout, 1);
	}
	if (red->type == REDIR_IN)
	{
		dup2(*stdin, 0);
		close(file);
	}
}

int	ft_red_out(char *file_name, int file, int *stdout)
{
	if (file != -1)
		close(file);
	file = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (*stdout == -1)
		*stdout = dup(1);
	file = dup2(file, 1);
	return (file);
}

int	ft_red_in(char *file_name, int file, int *stdin)
{
	(void)stdin;
	if (file != -1)
		close(file);
	file = open(file_name, O_RDONLY);
	if (file == -1)
	{
		printf("minishell: %s: No such file or directory\n", file_name);
		return (-5);
	}
	// if(*stdin == -1)
	//     *stdin = dup(0);
	// file = dup2(file,0);
	return (file);
}

int	ft_double_red_out(char *file_name, int file, int *stdout)
{
	if (file != -1)
		close(file);
	file = open(file_name, O_RDWR | O_APPEND | O_CREAT, 0777);
	if (*stdout == -1)
		*stdout = dup(1);
	file = dup2(file, 1);
	return (file);
}

int	ft_redirections(t_red *red, int *stdin, int *stdout)
{
	t_red	*tmp;
	int		file;

	tmp = red;
	file = -5;
	while (tmp)
	{
		if (tmp->type == REDIR_OUT)
			file = ft_red_out(tmp->file, file, stdout);
		else if (tmp->type == REDIR_IN)
			file = ft_red_in(tmp->file, file, stdin);
		else if (tmp->type == DREDIR_OUT)
			file = ft_double_red_out(tmp->file, file, stdout);
		if(file == -5)
			return(-5);
		// if(red->type == HERE_DOC)
		//     ft_red_out(red->file);
		tmp = tmp->next;
	}
	return (file);
}
