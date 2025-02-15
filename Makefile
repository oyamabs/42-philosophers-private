NAME=philo.out
CC=cc
CFLAGS=-Wall -Wextra -g -Werror -fsanitize=thread
SOURCEFILES=philo/philo.c philo/checkers.c philo/init.c philo/philoroutine.c philo/utils.c
OBJECTS=$(patsubst philo/%.c,objects/%.o,$(SOURCEFILES))
OBJDIR=objects

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

$(OBJDIR)/%.o: philo/%.c
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
