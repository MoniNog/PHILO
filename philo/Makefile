NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra 

SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
HEADERS = philo.h

all: $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(OBJS) -o $(NAME) $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all