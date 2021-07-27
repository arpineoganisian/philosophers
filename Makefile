NAME		= philo

HEADER_DIR	= includes

SRCS_LIST	= main.c parse.c get_time.c actions.c start_philosophers.c
SRCS		= $(addprefix $(SRCS_DIR)/, $(SRCS_LIST))
SRCS_DIR	= sources

OBJ_LIST 	= $(patsubst %.c, %.o, $(SRCS_LIST))
OBJ 		= $(addprefix $(OBJ_DIR)/, $(OBJ_LIST))
OBJ_DIR		= objects

CC			= gcc
CFLAGS		= -g -Wall -Werror -Wextra

RM			= rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -I $(HEADER_DIR) $(OBJ) -o $(NAME)
$(OBJ_DIR)/%.o : $(SRCS_DIR)/%.c | $(OBJ_DIR)
			$(CC) $(CFLAGS) -I $(HEADER_DIR) -c $< -o $@
$(OBJ_DIR):
			mkdir -p $@
clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re: fclean all

.PHONY: clean fclean all re