/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:56:26 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/12/24 21:31:40 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_move_player(t_vars *vars, double angle_offset)
{
    float x, y;
    int size;
    float collision_radius;

    size = vars->size;
    collision_radius = size / 5; 

    
    x = vars->player_x + cos((vars->angle + angle_offset) * M_PI / 180) * size / 10;
    y = vars->player_y;

    
    if (vars->map[(int)((y - collision_radius) / size)][(int)((x - collision_radius) / size)] != '1' &&
        vars->map[(int)((y + collision_radius) / size)][(int)((x - collision_radius) / size)] != '1' &&
        vars->map[(int)((y - collision_radius) / size)][(int)((x + collision_radius) / size)] != '1' &&
        vars->map[(int)((y + collision_radius) / size)][(int)((x + collision_radius) / size)] != '1')
    {
        vars->player_x = x;
    }

    
    x = vars->player_x;
    y = vars->player_y - sin((vars->angle + angle_offset) * M_PI / 180) * size / 10;

    
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

int	ft_move(int keycode, t_vars *vars)
{
	if (keycode == 53)
		ft_quit(vars);
	if (keycode == 13)
		ft_decide_direction(vars, 1); // Move up
	else if (keycode == 1)
		ft_decide_direction(vars, 2); // Move down
	else if (keycode == 0)
		ft_decide_direction(vars, 3); // Move left
	else if (keycode == 2)
		ft_decide_direction(vars, 4); // Move right
	else if (keycode == 124)
	{
		vars->angle -= 5;
		while (vars->angle >= 360)
			vars->angle -= 360;
	}
	else if (keycode == 123)
	{
		vars->angle += 5;
		while (vars->angle < 0)
			vars->angle += 360;
	}
	return (0);
}
