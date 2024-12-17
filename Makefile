# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: louisalah <louisalah@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/05 16:48:25 by asid-ahm          #+#    #+#              #
#    Updated: 2024/12/16 13:13:08 by louisalah        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCS = cub3d.c ./parsing/all_free.c ./parsing/initialize_vars.c gnl/get_next_line.c \
		./parsing/parse_colors.c ./parsing/printing_file.c ./parsing/validate_map.c\
		./parsing/parse_map.c ./parsing/parse_comps.c ./execute/mlx_init.c \
		./execute/move.c execute/render_map.c execute/math_help.c

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = mlx
MLX = $(MLX_DIR)/libmlx.a

CC = cc
CFLAGS = -g3 -I Includes -I $(LIBFT_DIR) -I $(MLX_DIR) -O3

OBJS = $(SRCS:.c=.o)
all: $(NAME)

$(LIBFT):
	make -C libft
$(MLX):
	make -C mlx

%.o: %.c
	$(CC) -Imlx -g3 -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -framework OpenGL -framework AppKit -o $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
