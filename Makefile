NAME = push_swap
CC = cc
CFLAGS = -Wextra -Wall
INC = -Ilibft/
LIBS = -Llibft -lft
LIBFT = libft/libft.a
SRCS = push_swap.c push_swap_utils.c push_swap_utils_stack.c
OBJS = $(SRCS:.c=.o)
RM = rm -rf

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft bonus

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

clean:
	$(RM) $(OBJS)
	make -C libft clean

fclean:
	$(RM) $(OBJS) $(NAME)
	make -C libft fclean

re:	fclean
	$(MAKE) all

.PHONY: all clean fclean re

