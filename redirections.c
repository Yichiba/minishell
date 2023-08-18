/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 12:58:55 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/17 18:37:56 by yichiba          ###   ########.fr       */
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

int	ft_herdoc(t_file *fide, int fd)
{
	int	file;

	file = -1;
	fide->std_in = dup(0);
	file = dup2(fd, 0);
	return (file);
}

int	ft_redirections(t_pars *parser, t_file *fide, t_std *std)
{
	t_red	*tmp;

	tmp = parser->red;
	std->file_in = -1;
	std->file_out = -1;
	while (tmp)
	{
		if (tmp->type == REDIR_OUT)
		std->file_out = ft_red_out(tmp->file, std->file_out, &fide->std_out);
		else if (tmp->type == REDIR_IN)
			std->file_in = ft_red_in(tmp->file, std->file_in, &fide->std_in);
		else if (tmp->type == DREDIR_OUT)
			std->file_out = ft_double_red_out(tmp->file, std->file_out,
					&fide->std_out);
		if (tmp->type == HERE_DOC)
			std->file_in = parser->here_doc;
		tmp = tmp->next;
	}
	return (0);
}
