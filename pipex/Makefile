NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS_FILES =  \
	utils.c \
	env.c \
	main.c \
	open.c \

OBJS = $(SRCS_FILES:.c=.o)

LIBFT = libft/libft.a

all: $(NAME)

$(NAME):$(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

$(LIBFT):
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
