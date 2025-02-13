NAME = libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIC

HEADER_DIR = ./includes
SRCS_DIR = ./srcs
OBJS_DIR = ./objs

INCLUDES = -I$(HEADER_DIR)

SRCS_FILES = \
	ft_printf.c \
	ft_convert.c \
	ft_convert_hex.c

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
