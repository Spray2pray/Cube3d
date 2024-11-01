NAME = cub3d

SRCS = cub3d.c get_next_line/get_next_line.c \
       $(wildcard libft/*.c)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address -I Includes -I libft

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re