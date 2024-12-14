/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisalah <louisalah@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:56:26 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/12/13 21:42:18 by louisalah        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_up(t_vars *vars)
{
	int x;
	int y;
	int size;

	size = vars->size;
	x = (vars->player_x + (cos((vars->angle * M_PI) / 180) * size/3))/size;
	y = vars->player_y/size;
	if (vars->map[y][x] != '1' && vars->map[y][x] != ' ')
		vars->player_x = vars->player_x + (cos((vars->angle * M_PI) / 180) * size/3);
	x = vars->player_x/size;
	y = (vars->player_y - (-sin((vars->angle * M_PI) / 180) * size/3))/size;
	if (vars->map[y][x] != '1' && vars->map[y][x] != ' ')
		vars->player_y = vars->player_y - (-sin((vars->angle * M_PI) / 180) * size/3);
}
static void	ft_down(t_vars *vars)
{
	int x;
	int y;
	int size;

	size = vars->size;
	y = vars->player_y/size;
	x = (vars->player_x - (cos((vars->angle * M_PI) / 180) * size/3))/size;
	if (vars->map[y][x] != '1' && vars->map[y][x] != ' ')
		vars->player_x = vars->player_x - (cos((vars->angle * M_PI) / 180) * size/3);
	x = vars->player_x/size;
	y = (vars->player_y + (-sin((vars->angle * M_PI) / 180) * size/3))/size;
	if (vars->map[y][x] != '1' && vars->map[y][x] != ' ')
		vars->player_y = vars->player_y + (-sin((vars->angle * M_PI) / 180) * size/3);
}
static void	ft_right(t_vars *vars)
{
	int x;
	int y;
	int size;

	size = vars->size;
	x = (vars->player_x + (-sin((vars->angle * M_PI) / 180) * size/3))/size;
	y = (vars->player_y + (cos((vars->angle * M_PI) / 180) * size/3))/size;
	if (vars->map[y][x] != '1' && vars->map[y][x] != ' ')
	{
		vars->player_x = vars->player_x + (-sin((vars->angle * M_PI) / 180) * size/3);
		vars->player_y = vars->player_y + (cos((vars->angle * M_PI) / 180) * size/3);
	}
}
static void	ft_left(t_vars *vars)
{
	int x;
	int y;
	int size;

	size = vars->size;
	x = (vars->player_x - (-sin((vars->angle * M_PI) / 180) * size/3))/size;
	y = (vars->player_y - (cos((vars->angle * M_PI) / 180) * size/3))/size;
	if (vars->map[y][x] != '1' && vars->map[y][x] != ' ')
	{
		vars->player_x = vars->player_x - (-sin((vars->angle * M_PI) / 180) * size/3);
		vars->player_y = vars->player_y - (cos((vars->angle * M_PI) / 180) * size/3);
	}
}

int	ft_move(int keycode, t_vars *vars)
{
	if (keycode == 53)
		ft_quit(vars);
	if (keycode == 13)
		ft_up(vars);
	else if (keycode == 1)
		ft_down(vars);
	else if (keycode == 0)
		ft_left(vars);
	else if (keycode == 2)
		ft_right(vars);
	else if (keycode == 124)
	{
		vars->angle += 5;
		while (vars->angle >= 360)
			vars->angle -= 360;
	}
	else if (keycode == 123)
	{
		vars->angle -= 5;
		while (vars->angle < 0)
			vars->angle += 360;
	}
	return (0);
}
