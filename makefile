NAME = minishell

SRCS = minishell.c enviremenr.c parser.c lexer.c lexer_outils.c pars_redir.c excutions.c syntax_errors.c\
	builtins_outils.c redirections.c execve.c builtins.c builtins1.c builtins2.c libft_fun1.c libft_fun3.c libft_fun2.c\
	free_allocations.c  redirections_outils.c expansion.c lexer_outils1.c excution1.c 

CC = cc
CFLAGS =  -Wall -Werror -Wextra
LDFLAGS = -L/Users/yichiba/goinfre/brew/opt/readline/lib -I/Users/yichiba/goinfre/brew/opt/readline/include -lreadline

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all
