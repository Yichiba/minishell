/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:14:31 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/10 11:55:17 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h> 

int g_exit;

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

typedef struct s_file
{
	int std_out;
	int std_in;
	int file;
	int i;
}t_file;

typedef struct s_pars
{
	char	**full_cmd;
	t_red	*red;
	int		args_num;
	struct s_pars *next;
}t_pars;

typedef struct s_global
{
	t_env	*env;
	t_file	fide;
	int		fd[2];
	int		id;
	int		*pids;
}	t_global;

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

char	*ft_strchr(const char *s, int c);
char 	*ft_substr(char *str,int start, int end);
char 	*ft_trim(char *str, char sep);
t_lex	*ft_lexer(char *input);
t_pars	*ft_parser(t_lex *lexer);
t_lex	*ft_syntax_pipe(t_lex * lexer);
t_pars	*add_new_node(t_lex *start,int args);
int 	ft_count_args(t_lex *start);
t_lex	*ft_clean(t_lex *lexer,t_env *env);

char	*ft_getenv(t_env *env, char *var);
t_env* ft_remove_node(t_env* env, char* data);
int		ft_strcmp(char *str, char *ptr);
int		variable_syntax(char *str);

void	ft_excutions( t_pars *parser, t_env *env);
t_env	*ft_builtins( t_pars *parser, t_env *env);
int		ft_strcmp(char *str, char *ptr);


char	*ft_dollar(char *input, int *i);
char	*ft_strdup(char *str);
t_lex	*ft_add(t_lex *lex, char *content, enum e_token type);
char	*ft_same_type(char *input, int *i);
t_lex	*ft_set_state(t_lex *lexer);
int		ft_atoi(char *str);
int		ft_alpha(char str);
int		ft_num(char str);
char	*set_var(char *input,int *i);
char	*get_state(enum e_state state);
char	*get_type(enum e_token token);
int		ft_strlen(char *str);
char	*ft_strjoin(char *str, char *tab);
t_lex	*remove_node(t_lex *lex, t_lex *node);
t_lex	*ft_remove_quote(t_lex *lexer);
t_lex	*ft_remove_space(t_lex *lexer);
t_red	*ft_add_red(t_red *red, char *file, int type);
t_lex	*ft_syntax_redir(t_lex *lexer);
t_red	*ft_red(t_lex *lexer,t_lex **start);
char	**get_full_cmd(t_lex *start,int args);
int		count_pipes(t_lex *lexer);


int		ft_redirections(t_red * red, t_file *fide);
void    close_file(t_red *red, t_file *fide);


void	ft_free(t_lex *lexer, t_pars *parser);

char	*ft_itoa(int n);
int ft_count(char *str,char sep);

int 	ft_is_builtins(char *str);
t_env   *find_commands(t_env *env,t_pars *parser);
char 	**ft_split(char *str, char sep);
char 	*substr(char *str,int start, int end);
int 	ft_count(char *str,char sep);
char    **ft_env_to_tab(t_env *env);
t_lex	*ft_syntax(t_lex *lexer);
void 	crate_pipe(t_pars *pars, t_lex *l, t_env *env);
void	*ft_calloc(size_t count, size_t size);
#endif