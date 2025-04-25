NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -pthread

SRC = $(wildcard src/*.c)
OBJDIR = obj
OBJS = $(SRC:src/%.c=$(OBJDIR)/%.o)
DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $@ $(CFLAGS)

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -MMD -c $< -o $@

-include $(DEPS)

clean:
	@rm -f $(OBJS) $(DEPS)

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJDIR)

re: fclean all

# valgrind --tool=helgrind -s ./philo
# to dataraces

# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./philo
