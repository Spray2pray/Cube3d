/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisalah <louisalah@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:11:18 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/12/16 13:19:33 by louisalah        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_put_pixel(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static void	draw_square(t_vars *vars, int x_start, int y_start, int color)
{
	int	x;
	int	y;

	y = y_start;
	while (y + 1 < y_start + vars->size)
	{
		x = x_start;
		while (x + 1 < x_start + vars->size)
		{
			my_put_pixel(vars, x, y, color);
			x++;
		}
		y++;
	}
}

int check_dist(float x, float y, t_vars *vars, float angle)
{
	int dist = 0;
	int size = vars->size;

	while (vars->map[(int)(y / size)][(int)(x / size)] == '0')
	{
		x += cos((angle * M_PI) / 180);
		y -= sin((angle * M_PI) / 180);
		dist++;
	}
	return (dist);
}

// void	draw_3d_line(t_vars *vars, float x, int dist, float angle)
// {
// 	float y = 0;

// 	dist *= cos(((angle - vars->angle) * M_PI) / 180)*1.5;
// 	y += dist;
// 	while (y < (1000 - dist))
// 	{
// 		my_put_pixel(vars, x, y, 0x0000FF);
// 		y++;
// 	}
// }

static void	draw_cursor(t_vars *vars, float x_start, float y_start, int color)
{
	int		i;
	float	j;
	float	fov;
	float	angle;
	int		x;
	int		y;
	int		n;
	int		k;

	j = -30;
	k = 0;
	fov = (60.0 / 1000);
	angle = vars->angle;
	x = x_start;
	y = y_start;
	while (j <= 30)
	{
		i = 0;
		x_start = x;
		y_start = y;
		n = check_dist(x_start, y_start, vars, angle+j);
		while (i++ < n)
		{
			my_put_pixel(vars, x_start, y_start, color);
			x_start += cos(((angle+j) * M_PI) / 180);
			y_start -= sin(((angle+j) * M_PI) / 180);
		}
		j += fov;
	}
}

void	draw_player(t_vars *vars, int x_start, int y_start, int color)
{
	const int	size = vars->size / 3;
	int			x;
	int			y;

	y = y_start;
	while (y + 1 < y_start + size)
	{
		x = x_start;
		while (x + 1 < x_start + size)
		{
			my_put_pixel(vars, x, y, color);
			x++;
		}
		y++;
	}
	draw_cursor(vars, x_start + size / 2, y_start + size / 2, 16711680);
}

int rgb_to_hex(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	draw_splited_screen(t_vars *vars)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 1000)
	{
		j = -1;
		while (++j < 1000)
		{
			if (i < 500)
				my_put_pixel(vars, j, i, rgb_to_hex(vars->ceiling_colors[0], vars->ceiling_colors[1], vars->ceiling_colors[2]));
			else
				my_put_pixel(vars, j, i, rgb_to_hex(vars->floor_color[0], vars->floor_color[1], vars->floor_color[2]));
		}
	}
}

int	draw_map2d(t_vars *vars)
{
	int	i;
	int	j;

	i = -1;
	ft_memset(vars->addr, 0, vars->line_length * 1000);
	draw_splited_screen(vars);
	while (vars->map[++i])
	{
		j = -1;
		while (vars->map[i][++j])
		{
			if (vars->map[i][j] == '1')
				draw_square(vars, (j * vars->size), (i * vars->size), 0xD3D3D3);
			else if(vars->map[i][j] == '0' || check_for_player(vars->map[i][j]))
				draw_square(vars, (j * vars->size), (i * vars->size), 0x404040);
		}
	}
	draw_player(vars, vars->player_x, vars->player_y, 0x000000CD);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img, 0, 0);
	return (0);
}
