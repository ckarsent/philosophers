NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra #-fsanitize=thread

SRCS = init.c \
		main.c \
		monitor.c \
		monitor2.c \
		parsing.c \
		philo_utils.c \
		routine.c \
		routine2.c \
		time.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY = all clean fclean re
