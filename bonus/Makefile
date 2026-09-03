NAME = checker

SRCS = checker.c checker_utils.c checker_moves.c

OBJS = $(SRCS:c=o)

RM = rm -Rf
CFLAGS = -Wextra -Wall
LIB_DIR = ../libft
INC = -Ilibft/
LIBS = -L$(LIB_DIR) -lft
LIBFT = $(LIB_DIR)/libft.a

all: $(NAME) $(LIBFT)


$(LIBFT):
	make -C $(LIB_DIR) bonus

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)


clean:
	$(RM) $(OBJS)
	make -C $(LIB_DIR) clean

fclean:
	$(RM) $(OBJS) $(NAME)
	make -C $(LIB_DIR) fclean

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re
