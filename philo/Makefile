NAME=philo

SRC= philo_main.c philo_list.c philo_error1.c

OBF1= $(SRC:%.c=$(OBF_DIR)/%.o) $(UTIL1:%.c=$(OBF_DIR)/%.o)

OBF= $(addprefix $(OBF_DIR)/, $(OBF1))

HEADER= philo_all.h

UTIL1= ft_atoi.c philo_util.c

OBF_DIR= OBF

CC= gcc

CFLAGS= -g -Wall -Wextra -Werror -o

SAN= -fsanitize=thread

OO= -O3

all:$(NAME)

$(NAME): $(OBF_DIR) $(OBF1) 
	$(CC) $(CFLAGS) $@ $(OBF1)

$(OBF_DIR):
	mkdir $(OBF_DIR)

$(OBF_DIR)/%.o: %.c $(HEADER)
	$(CC) -c $(CFLAGS) $@ $<

clean:
	@rm -f $(OBF) $(OBF_DIR)

fclean:
	@rm -rf $(OBF) $(OBF_DIR) $(NAME)

f: fclean

re:
	@$(MAKE) fclean
	@$(MAKE) all

run1: $(NAME)
	@./$(NAME) 5 700 250 249 10

run: $(NAME)
	@./$(NAME) 5 760 250 200 5

run200: $(NAME)
	@./$(NAME) 200 410 200 200

bug:
	lldb $(NAME)

Norm:
	norminette $(SRC) $(UTIL1) $(HEADER)

.PHONY: all clean fclean f re Norm