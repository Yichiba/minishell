/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 12:58:55 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/12 17:46:23 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_red_in(char *file_name, int file, int *std_in)
{
	(void)std_in;
	if (file != -1)
		close(file);
	file = open(file_name, O_RDONLY);
	if (file == -1)
	{
		printf("minishell: %s: No such file or directory\n", file_name);
		return (-5);
	}
	if (*std_in == -1)
		*std_in = dup(0);
	file = dup2(file, 0);
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

int	ft_herdoc(t_file *fide,int fd)
{
	int file = -1;
	fide->std_in = dup(0);
	file  = dup2(fd,0);
	return(file);
	
}

int	ft_redirections(t_red *red, t_file *fide)
{
	t_red	*tmp;
	int		file;

	tmp = red;
	file = -5;
	while (tmp)
	{
		if (tmp->type == REDIR_OUT)
			file = ft_red_out(tmp->file, file, &fide->std_out);
		else if (tmp->type == REDIR_IN)
			file = ft_red_in(tmp->file, file, &fide->std_in);
		else if (tmp->type == DREDIR_OUT)
			file = ft_double_red_out(tmp->file, file, &fide->std_out);
		if (file == -5)
			return (-5);
		if(tmp->type == HERE_DOC)
			file  = ft_herdoc(fide,red->herdoc);
		tmp = tmp->next;
	}
	return (file);
}
