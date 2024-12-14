/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisalah <louisalah@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:33:33 by mbamatra          #+#    #+#             */
/*   Updated: 2024/12/13 20:27:43 by louisalah        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "../gnl/get_next_line.h"
# include "../libft/libft.h"
# include "../mlx/mlx.h"

typedef struct s_vars
{
	int		angle;
	void	*mlx;
	void	*mlx_win;
	void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		map_fd;
	int		size;
	char	*map_name;
	int		floor_color[3];
	int		ceiling_colors[3];
	int		map_height;
	int		player_x;
	int		player_y;
}	t_vars;


void	initialize_vars(t_vars *vars, char **argv);
void	init_flags(int *flag);
void	free_double(char **map, char *str);
void	free_all(t_vars *vars);
int		parse_floor(t_vars *vars, char *str);
int		parse_ceiling(t_vars *vars, char *str);
int		check_for_player(char c);
int		validate(t_vars *vars);
void	print_comps(t_vars *vars);
int		check_map_start(char *line);
int		validate_characters(t_vars *vars);
void	print_map(t_vars *vars);
int		filling_map(t_vars *vars, char *line, int fd);
int		read_map(t_vars *vars, char *file);

int		init_mlx(t_vars *vars);
int		ft_quit(t_vars *map);
int		ft_move(int keycode, t_vars *map);
void	draw_player(t_vars *vars, int x_start, int y_start, int color);
int		draw_map2d(t_vars *vars);
int		round_down(float x);
#endif