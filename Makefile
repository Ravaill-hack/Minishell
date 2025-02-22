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

INCLUDES = -I$(HEADER_DIR) -I$(LIBFT_HEADER_DIR) 
LIBRARIES = -L$(LIBFT_DIR) -lft

SRCS_FILES = \
	main.c \
	init.c \
	parsing.c \
	token.c \
	free.c \
	handle_cmd.c \
	handle_errors.c \
	handle_signal.c \
	termios_utils.c \
	debug.c \
	cmd.c \
	cmd_2.c \
	cmd_3.c \
	exec_cmd.c \
	extract_env.c \
	update_env.c \
	utils.c \
	modify_shlvl.c \

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
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
