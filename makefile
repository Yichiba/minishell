NAME = minishell

SRCS = minishell.c enviremenr.c parser.c print.c lexer.c lexer_outils.c pars_redir.c builtins.c

CC = cc

CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g


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