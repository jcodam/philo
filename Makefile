NAME=philo

SRC= philo_main.c philo_list.c philo_error1.c

OBF= $(SRC:.c=.o)

HEADER= philo_all.h

UTIL1= ft_atoi.c philo_util.c

UTIL= $(UTIL1:.c=.o)

CC= gcc

CFLAGS= -g -Wall -Wextra -Werror -o

SAN= -fsanitize=thread

OO= -O3

all:$(NAME)

pr:
	$(CC) $(CFLAGS) practes practes.c

pf:
	rm -f practes

$(NAME): $(OBF) $(UTIL)
	$(CC) $(CFLAGS) $@ $^

%.o: %.c $(HEADER)
	$(CC) -c $(CFLAGS) $@ $<

clean:
	rm -f $(OBF) $(UTIL)

fclean:
	@rm -f $(OBF) $(UTIL) $(NAME)

f: fclean

re:
	@$(MAKE) fclean
	@$(MAKE) all

run1:
	@./$(NAME) 5 700 250 249 10

run:
	@./$(NAME) 5 760 250 200 5

run200:
	@./$(NAME) 200 410 200 200

bug:
	lldb $(NAME)

Norm:
	norminette $(SRC) $(UTIL1) $(HEADER)

.PHONY: all clean fclean f re Norm