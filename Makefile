NAME=philo

SRC= philo_main.c philo_list.c philo_error1.c

OBF= $(SRC:.c=.o)

HEADER= philo_all.h

UTIL1= ft_atoi.c 

UTIL= $(UTIL1:.c=.o)

CC= gcc

CFLAGS= -g -Wall -Wextra -Werror -o

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
	rm -f $(OBF) $(UTIL) $(NAME)

f: fclean

re:
	$(MAKE) fclean
	$(MAKE) all

run:
	./$(NAME) 5 500 100 200

bug:
	lldb $(NAME)

Norm:
	norminette $(SRC) $(UTIL1) $(HEADER)

.PHONY: all clean fclean f re Norm