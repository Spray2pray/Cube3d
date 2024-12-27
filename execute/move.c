/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisalah <louisalah@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:56:26 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/12/27 14:34:35 by louisalah        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_move_player(t_vars *vars, float angle_offset)
{
    float x, y;
    int size;
    float collision_radius;

    size = vars->size;
    collision_radius = size / 5; 

    
    x = vars->player_x + cos((vars->angle + angle_offset) * M_PI / 180) * size / 5;
    y = vars->player_y;

    
    if (vars->map[(int)((y - collision_radius) / size)][(int)((x - collision_radius) / size)] != '1' &&
        vars->map[(int)((y + collision_radius) / size)][(int)((x - collision_radius) / size)] != '1' &&
        vars->map[(int)((y - collision_radius) / size)][(int)((x + collision_radius) / size)] != '1' &&
        vars->map[(int)((y + collision_radius) / size)][(int)((x + collision_radius) / size)] != '1')
    {
        vars->player_x = x;
    }

    
    x = vars->player_x;
    y = vars->player_y - sin((vars->angle + angle_offset) * M_PI / 180) * size / 5;

    
    if (vars->map[(int)((y - collision_radius) / size)][(int)((x - collision_radius) / size)] != '1' &&
        vars->map[(int)((y + collision_radius) / size)][(int)((x - collision_radius) / size)] != '1' &&
        vars->map[(int)((y - collision_radius) / size)][(int)((x + collision_radius) / size)] != '1' &&
        vars->map[(int)((y + collision_radius) / size)][(int)((x + collision_radius) / size)] != '1')
    {
        vars->player_y = y;
    }
}

static void	ft_decide_direction(t_vars *vars, int direction)
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
	{

        vars->key_right = 1;
	}
    else if (keycode == LEFT)
	{

        vars->key_left = 1;
	}
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
	{

        vars->key_right = 0;
	}
    else if (keycode == LEFT)
	{

        vars->key_left = 0;
	}
	return (0);
}

int ft_handle_keys(t_vars *vars)
{
    if (vars->key_w)
        ft_decide_direction(vars, 1);
    if (vars->key_s)
        ft_decide_direction(vars, 2);
    if (vars->key_a)
        ft_decide_direction(vars, 3);
    if (vars->key_d)
        ft_decide_direction(vars, 4);
    if (vars->key_right)
    {
        vars->angle -= 10;
        while (vars->angle >= 360)
            vars->angle -= 360;
    }
    if (vars->key_left)
    {
        vars->angle += 10;
        while (vars->angle < 0)
            vars->angle += 360;
    }
	render(vars);
    return (0);
}

