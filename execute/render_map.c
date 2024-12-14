/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisalah <louisalah@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:11:18 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/12/13 19:45:13 by louisalah        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void my_put_pixel(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static void	draw_square(t_vars *vars, int x_start, int y_start, int color)
{
	int	x;
	int	y;
	// char	*dst;

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


static void	draw_cursor(t_vars *vars, float x_start, float y_start, int color)
{
	int	i = 0;

	
	while (i++ < 50)
	{
		my_put_pixel(vars, x_start, y_start, color);
		x_start += cos((vars->angle * M_PI) / 180);
		y_start += sin((vars->angle * M_PI) / 180);
	}
}

void	draw_player(t_vars *vars, int x_start, int y_start, int color)
{
	const int	size = vars->size / 3;
	int			x;
	int			y;
	// char		*dst;

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
	draw_cursor(vars, x_start + size / 2, y_start + size / 2, 0x000000CD);
}

int	draw_map2d(t_vars *vars)
{
	int	i;
	int	j;

	i = -1;
	ft_memset(vars->addr, 0, vars->line_length * 1000);
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
