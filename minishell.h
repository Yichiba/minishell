/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:00:07 by ybourais          #+#    #+#             */
/*   Updated: 2023/07/10 12:08:18 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <fcntl.h> /* open */
#include <string.h> /* open */
# include <stdio.h> /* printf strerror perror*/
#include <readline/readline.h> /* redline */
#include <readline/history.h> /* redline */
#include <stdlib.h> /* malloc, free getenv */
#include <unistd.h> /* access, fork, getcwd, chdir, unlink execve dup dup2 pipe isatty ttyname ttyslot*/
#include <sys/wait.h> /* waitpid */
#include <sys/stat.h> /* stat */
#include <dirent.h> /* opendir readdir closedir*/
#include <sys/ioctl.h> /* ioctl */
#include <termios.h> /* tcsetattr */
#include <termcap.h> /* tgetent */

typedef struct s_list
{	
	char *var;
	char *str;
	struct s_list *next;
}t_env;

void	check_quoting(char *str);
char	*set_variables(char*str);
int 	ft_var_name(char *str);
t_env 	*ft_builtins(t_env * env,char **tab);
t_env	*ft_export(t_env *env,char **tab);
t_env 	*ft_add_back(char *str);
int		ft_strstr(char *str, char *ptr);
t_env 	*ft_env(char **tab);

#endif