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
	token_append.c \
	token_check.c \
	token_error.c \
	token_extract.c \
	token_len.c \
	token_parsing.c \
	token_parsing_2.c \
	token_utils.c \
	free.c \
	free_2.c \
	handle_cmd.c \
	handle_errors.c \
	handle_signal.c \
	termios_utils.c \
	debug.c \
	cmd_exit.c \
	cmd_env_unset.c \
	cmd_export_pwd.c \
	cmd_cd.c \
	cmd_echo.c \
	exec_cmd.c \
	extract_env.c \
	update_env.c \
	update_env_2.c \
	redirection_build.c \
	redirection_handle.c \
	cmd_list_init.c \
	cmd_list_build.c \
	cmd_list_utils.c \
	cmd_list_len.c \
	utils.c \
	handle_pipes.c \

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
