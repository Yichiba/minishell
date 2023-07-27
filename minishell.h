/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:14:31 by yichiba           #+#    #+#             */
/*   Updated: 2023/07/27 22:59:58 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
#include <readline/readline.h>
#include <readline/history.h> 

typedef struct s_env
{
	char	*var;
	char	*str;
	struct s_env	*next;
}t_env;


enum e_token
{
	WHITE_SPACE = ' ',
	QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	ESCAPE = '\\',
	VAR = '$',
	PIPE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	WORD,
	HERE_DOC,
	DREDIR_OUT,
};

enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
};

typedef struct s_lex
{
	char	*content;
	enum e_token	type;
	enum e_state	state;
	struct s_lex	*next;
}t_lex;
typedef struct s_red
{
	char *file;
	int	type;
	struct s_red *next;
}t_red;

typedef struct s_pars
{
	char	**full_cmd;
	t_red	*red;
	int		args_num;
	struct s_pars *next;
}t_pars;

int ft_strlen(char *str);
t_env	*get_env(char **tab);
void	ft_print_env(t_env *env);
char	*set_variables_name(char*str);
char	*set_value(char*str);
// char	*set_variables(char*str);
// char	*set_value(char*str);
t_env	*ft_add_back(char *str);
char	*ft_strdup(char *str);
t_lex	*remove_node(t_lex *lex, t_lex *node);


void	ft_print_lexer(t_lex *lexer);
void	ft_print_red(t_red *red);
void	ft_print_env(t_env *env);
void 	ft_print_parser(t_pars *parser);



t_lex	*ft_lexer(char *input);
t_pars	*ft_parser(t_lex *lexer);
int		ft_syntax_pipe(t_lex * lexer);
t_pars	*add_new_node(t_lex *start,int args);
int 	ft_count_args(t_lex *start);
t_lex	*ft_clean(t_lex *lexer,t_env *env);



t_env	*ft_builtins( t_pars *parser, t_env *env);
int		ft_strcmp(char *str, char *ptr);



char	*ft_dollar(char *input, int *i);
char	*ft_strdup(char *str);
t_lex	*ft_add(t_lex *lex, char *content, enum e_token type);
char	*ft_same_type(char *input, int *i);
t_lex	*ft_set_state(t_lex *lexer);
int		ft_alpha(char str);
int		ft_num(char str);
char	*set_var(char *input,int *i);
char	*get_state(enum e_state state);
char	*get_type(enum e_token token);
int		ft_strlen(char *str);
char	*ft_strjoin(char *str, char *tab);
t_lex	*ft_join(t_lex *tmp, t_lex *next);
t_lex	*remove_node(t_lex *lex, t_lex *node);
t_lex	*ft_remove_quote(t_lex *lexer);
t_lex	*ft_remove_space(t_lex *lexer);
t_red	*ft_add_red(t_red *red, char *file, int type);
int		ft_syntax_redir(t_lex *lexer);
t_red	*ft_red(t_lex *lexer);
char	**get_full_cmd(t_lex *start,int args);
int		count_pipes(t_lex *lexer);


#endif