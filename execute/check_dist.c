/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 18:12:36 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/12/27 18:12:50 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	update_hit_type(t_vars *vars, t_data *data)
{
	if (data->new_y != data->current_y && data->new_x != data->current_x)
	{
		if (ft_abs(data->new_y - data->current_y)
			> ft_abs(data->new_x - data->current_x))
			vars->hit_type = 'H';
		else
			vars->hit_type = 'V';
	}
	if (data->new_y != data->current_y)
		vars->hit_type = 'H';
	else if (data->new_x != data->current_x)
		vars->hit_type = 'V';
}

int	check_dist(t_vars *vars, float angle)
{
	t_data	data;

	data.dist = 0;
	data.x_step = cos((angle * M_PI) / 180);
	data.y_step = -sin((angle * M_PI) / 180);
	data.current_x = (int)(vars->r_x / vars->size);
	data.current_y = (int)(vars->r_y / vars->size);
	while (vars->map[data.current_y][data.current_x] == '0')
	{
		data.next_x = vars->r_x + data.x_step;
		data.next_y = vars->r_y + data.y_step;
		data.new_x = (int)(data.next_x / vars->size);
		data.new_y = (int)(data.next_y / vars->size);
		if (data.new_x != data.current_x || data.new_y != data.current_y)
			update_hit_type(vars, &data);
		data.current_x = data.new_x;
		data.current_y = data.new_y;
		vars->r_x = data.next_x;
		vars->r_y = data.next_y;
		data.dist++;
	}
	return (data.dist);
}
