NAME=philo

OBF=

HEADER=

UTIL=

CC= gcc

CFLAGS= -g -Wall -Wextra -Werror -o

OO= -O3

all:$(NAME)

pr:
	$(CC) $(CFLAGS) practes practes.c

pf:
	rm practes

$(NAME): $(OBF)
	$(CC) $(CFLAGS) $@ $^

%.o: %.c $(HEADER)
	$(CC) -c $(CFLAGS) $@ $<

clean:
	rm -f $(OBF)

fclean:
	rm -f $(OBF) $(NAME)

f: fclean

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean f re