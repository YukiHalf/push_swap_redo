NAME = push_swap
CC = cc
CFLAGS = -Wextra -Wall
INC = -Ilibft/
LIBS = -Llibft -lft
LIBFT = libft/libft.a
SRCS = push_swap.c
OBJS = $(SRCS:c=o)
RM = rm -rf

all: $(NAME) $(LIBFT)

$(LIBFT):
	make -c libft

$(NAME):
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

clean:
	$(RM) $(OBJS)
	make -f libft clean

fclean:
	$(RM) $(OBJS) $(NAME)
	make -f libft fclean

re:	fclean
	$(MAKE) all

.PHONY: all clean fclean re

