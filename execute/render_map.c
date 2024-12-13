/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:11:18 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/12/13 15:30:29 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
			mlx_pixel_put(vars->mlx, vars->mlx_win, x, y, color); // mlx_pixel_put is really slow. Make your own.
			x++;
		}
		y++;
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
			mlx_pixel_put(vars->mlx, vars->mlx_win, x, y, color); // make your own.
			x++;
		}
		y++;
	}
}
int	draw_map2d(t_vars *vars)
{
	int	i;
	int	j;

	i = -1;
	// mlx_clear_window(vars->mlx, vars->mlx_win);
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
	return (0);
}
