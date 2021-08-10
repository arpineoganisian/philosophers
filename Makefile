NAME		= philo

HEADER_DIR	= includes

SRCS_LIST	= main.c actions_of_philosopthers.c monitoring_threads.c \
			parse.c run_philosophers.c time_utils.c
SRCS		= $(addprefix $(SRCS_DIR)/, $(SRCS_LIST))
SRCS_DIR	= sources

OBJ_LIST 	= $(patsubst %.c, %.o, $(SRCS_LIST))
OBJ 		= $(addprefix $(OBJ_DIR)/, $(OBJ_LIST))
OBJ_DIR		= objects

CC			= gcc
CFLAGS		= -g -Wall -Werror -Wextra -pthread

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
	$(RM) $(NAME) $(OBJ_DIR)
re: fclean all

.PHONY: clean fclean all re