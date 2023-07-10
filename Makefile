NAME = minishell

SRCS = minishell.c parssing.c envirement.c

CC = cc

CFLAGS = -Wall -Werror -Wextra #-g -fsanitize=address

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS)  $(OBJS) -o $(NAME) -lreadline -ltermcap
clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all