/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:33:33 by mbamatra          #+#    #+#             */
/*   Updated: 2024/12/27 19:31:22 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../gnl/get_next_line.h"
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

enum		e_keys
{
	W = 13,
	S = 1,
	A = 0,
	D = 2,
	RIGHT = 124,
	LEFT = 123,
	ESC = 53
};

typedef struct s_img
{
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*img;
	char	*addr;
}			t_img;

typedef struct s_data
{
	int		current_x;
	int		current_y;
	float	new_x;
	float	new_y;
	float	next_x;
	float	next_y;
	float	x_step;
	float	y_step;
	float	dist;
	int		x;
	int		y;
	float	angle;
	float	t_x;
	float	t_y;
}			t_data;

typedef struct s_vars
{
	t_img	*north;
	t_img	*south;
	t_img	*west;
	t_img	*east;
	int		dist;
	float	ray_angle;
	int		key_w;
	int		key_s;
	int		key_a;
	int		key_d;
	int		key_left;
	int		key_right;
	int		angle;
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	**map;
	char	hit_type;
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
	float	r_x;
	float	r_y;
	float	player_x;
	float	player_y;
}			t_vars;

void		render(t_vars *vars);
void		initialize_vars(t_vars *vars, char **argv);
void		init_flags(int *flag);
void		free_double(char **map, char *str);
void		free_all(t_vars *vars);
int			parse_floor(t_vars *vars, char *str);
int			parse_ceiling(t_vars *vars, char *str);
int			check_for_player(char c);
int			validate(t_vars *vars);
int			check_map_start(char *line);
int			validate_characters(t_vars *vars);
int			filling_map(t_vars *vars, char *line, int fd, int i);
int			read_map(t_vars *vars, char *file);

int			init_mlx(t_vars *vars);
int			ft_quit(t_vars *map);
int			draw(t_vars *vars);
float		ft_abs(float i);
int			my_mlx_pixel_get(t_img *img, int x, int y);
int			ft_key_press(int keycode, t_vars *vars);
int			ft_key_release(int keycode, t_vars *vars);
int			ft_handle_keys(t_vars *vars);
float		adjust_float_angle(float angle);
int			ft_handle_keys(t_vars *vars);
void		ft_decide_direction(t_vars *vars, int direction);
int			rgb_to_hex(int r, int g, int b);
void		my_put_pixel(t_vars *vars, int x, int y, int color);
int			my_mlx_pixel_get(t_img *img, int x, int y);
void		draw_cursor(t_vars *vars, float angle, float fov);
int			check_dist(t_vars *vars, float angle);
t_img		*get_texture_img(t_vars *vars);
float		get_texture_x(t_vars *vars, t_img *txt_img);

#endif