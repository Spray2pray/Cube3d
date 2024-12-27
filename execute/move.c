/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:56:26 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/12/27 17:06:38 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	ft_check_collision(t_vars *vars, float x, float y)
{
	int		size;
	float	collision_radius;

	size = vars->size;
	collision_radius = size / 5;
	if (vars->map[(int)((y - collision_radius) / size)][(int)((x
				- collision_radius) / size)] != '1' && vars->map[(int)((y
				+ collision_radius) / size)][(int)((x - collision_radius)
			/ size)] != '1' && vars->map[(int)((y - collision_radius)
			/ size)][(int)((x + collision_radius) / size)] != '1'
		&& vars->map[(int)((y + collision_radius) / size)][(int)((x
				+ collision_radius) / size)] != '1')
	{
		return (1);
	}
	return (0);
}

static void	ft_move_player(t_vars *vars, float angle_offset)
{
	int		size;
	float	x;
	float	y;

	size = vars->size;
	x = vars->player_x + cos((vars->angle + angle_offset) * M_PI / 180) * size
		/ 5;
	y = vars->player_y;
	if (ft_check_collision(vars, x, y))
		vars->player_x = x;
	x = vars->player_x;
	y = vars->player_y - sin((vars->angle + angle_offset) * M_PI / 180) * size
		/ 5;
	if (ft_check_collision(vars, x, y))
		vars->player_y = y;
}

void	ft_decide_direction(t_vars *vars, int direction)
{
	if (direction == 1)
		ft_move_player(vars, 0);
	else if (direction == 2)
		ft_move_player(vars, 180);
	else if (direction == 3)
		ft_move_player(vars, 90);
	else if (direction == 4)
		ft_move_player(vars, 270);
}

int	ft_key_press(int keycode, t_vars *vars)
{
	if (keycode == W)
		vars->key_w = 1;
	else if (keycode == S)
		vars->key_s = 1;
	else if (keycode == A)
		vars->key_a = 1;
	else if (keycode == D)
		vars->key_d = 1;
	else if (keycode == RIGHT)
		vars->key_right = 1;
	else if (keycode == LEFT)
		vars->key_left = 1;
	else if (keycode == ESC)
		ft_quit(vars);
	return (0);
}

int	ft_key_release(int keycode, t_vars *vars)
{
	if (keycode == W)
		vars->key_w = 0;
	else if (keycode == S)
		vars->key_s = 0;
	else if (keycode == A)
		vars->key_a = 0;
	else if (keycode == D)
		vars->key_d = 0;
	else if (keycode == RIGHT)
		vars->key_right = 0;
	else if (keycode == LEFT)
		vars->key_left = 0;
	return (0);
}
