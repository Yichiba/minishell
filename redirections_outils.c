/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_outils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 20:20:41 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/17 14:54:50 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_file(t_red *red, t_file *fide)
{
	if (red->type == REDIR_OUT || red->type == DREDIR_OUT)
	{
		close(fide->file);
		dup2(fide->std_out, 1);
	}
	if (red->type == REDIR_IN)
	{
		dup2(fide->std_in, 0);
		close(fide->file);
	}
}
