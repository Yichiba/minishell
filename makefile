NAME = minishell

SRCS = minishell.c enviremenr.c parser.c print.c lexer.c lexer_outils.c pars_redir.c excutions.c syntax_errors.c\
	builtins_outils.c redirections.c execve.c builtins.c builtins1.c builtins2.c libft_fun1.c libft_fun3.c libft_fun2.c\
	free_allocations.c  redirections_outils.c expansion.c

			

CC = cc

CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g
# CFLAGS = -fsanitize=address -g


OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline -ltermcap
clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean
		make