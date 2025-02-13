NAME = minishell

LIBFT = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

HEADER_DIR = includes
SRCS_DIR = srcs
OBJS_DIR = objs

LIBFT_DIR = ./libft
LIBFT_HEADER_DIR = $(LIBFT_DIR)/includes
LIBFT_SRCS_DIR = ./srcs

INCLUDES = -I$(LIBFT_HEADER_DIR)
LIBRARIES = -L$(LIBFT_DIR)

SRCS_FILES = \
	main.c \

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS_FILES:.c=.o))

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBRARIES) -o $(NAME) -lncurses -lreadline

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -rf $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(FDF)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
