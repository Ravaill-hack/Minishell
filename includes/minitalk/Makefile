CLIENT = client
SERVER = server
FT_PRINTF = libftprintf.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

CLIENT_DIR = client
SERVER_DIR = server

CLIENT_HEADER_DIR = ./includes/$(CLIENT_DIR)
CLIENT_SRCS_DIR = ./srcs/$(CLIENT_DIR)
CLIENT_OBJS_DIR = ./objs/$(CLIENT_DIR)

SERVER_HEADER_DIR = ./includes/$(SERVER_DIR)
SERVER_SRCS_DIR = ./srcs/$(SERVER_DIR)
SERVER_OBJS_DIR = ./objs/$(SERVER_DIR)

FT_PRINTF_DIR = ./ft_printf
FT_PRINTF_HEADER_DIR = $(FT_PRINTF_DIR)/includes
FT_PRINTF_SRCS_DIR = ./srcs

CLIENT_INCLUDES = -I$(CLIENT_HEADER_DIR) -I$(FT_PRINTF_HEADER_DIR)
SERVER_INCLUDES = -I$(SERVER_HEADER_DIR) -I$(FT_PRINTF_HEADER_DIR)

LIBRARIES =  -L$(FT_PRINTF_DIR) -lftprintf

CLIENT_SRCS_FILES = \
			client.c \
			client_send_bytes.c \
			client_utils.c

SERVER_SRCS_FILES = server.c

CLIENT_OBJS = $(addprefix $(CLIENT_OBJS_DIR)/, $(CLIENT_SRCS_FILES:.c=.o))
SERVER_OBJS = $(addprefix $(SERVER_OBJS_DIR)/, $(SERVER_SRCS_FILES:.c=.o))

all: $(FT_PRINTF) $(CLIENT) $(SERVER)

$(FT_PRINTF):
	$(MAKE) -C $(FT_PRINTF_DIR)

$(CLIENT): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(CLIENT_INCLUDES) $(CLIENT_OBJS) $(LIBRARIES) -o $(CLIENT)

$(SERVER): $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(SERVER_INCLUDES) $(SERVER_OBJS) $(LIBRARIES) -o $(SERVER)

$(CLIENT_OBJS_DIR)/%.o: $(CLIENT_SRCS_DIR)/%.c
	@mkdir -p $(CLIENT_OBJS_DIR)
	$(CC) $(CFLAGS) $(CLIENT_INCLUDES) -c $< -o $@

$(SERVER_OBJS_DIR)/%.o: $(SERVER_SRCS_DIR)/%.c
	@mkdir -p $(SERVER_OBJS_DIR)
	$(CC) $(CFLAGS) $(SERVER_INCLUDES) -c $< -o $@

clean:
	rm -f $(CLIENT_OBJS) $(SERVER_OBJS)
	$(MAKE) -C $(FT_PRINTF_DIR) clean

fclean: clean
	rm -f $(CLIENT) $(SERVER)
	$(MAKE) -C $(FT_PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re