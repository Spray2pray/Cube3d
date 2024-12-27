/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:20:48 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/12/27 18:28:28 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static float	adjust_dist(t_vars *vars, float dist, float angle)
{
	dist *= cos(((angle - vars->angle) * M_PI) / 180) * 1.5;
	return ((vars->size / dist) * ((1080 / 2) / tan((30 * M_PI) / 180)));
}

static void	draw_3d_line(t_vars *vars, t_img *txt_img, t_data data)
{
	int		y;
	int		color;
	float	max;
	float	y_step;
	float	dist;

	dist = adjust_dist(vars, vars->dist, data.angle);
	data.t_x = get_texture_x(vars, txt_img);
	data.t_y = 0;
	y_step = (float)txt_img->height / dist;
	y = (1080 / 2) - (dist / 2);
	if (y < 0)
		y = 0;
	max = (1080 / 2) + (dist / 2);
	while (y < max && y < 1080)
	{
		color = my_mlx_pixel_get(txt_img, data.t_x, data.t_y);
		my_put_pixel(vars, data.x, y, color);
		data.t_y += y_step;
		y++;
	}
}

void	draw_cursor(t_vars *vars, float angle, float fov)
{
	float	j;
	t_img	*txt_img;
	t_data	data;

	j = -30;
	data.x = 1080;
	vars->angle = adjust_float_angle(vars->angle);
	while (j <= 30)
	{
		data.angle = angle + j;
		vars->dist = check_dist(vars, data.angle);
		vars->ray_angle = adjust_float_angle(data.angle);
		txt_img = get_texture_img(vars);
		draw_3d_line(vars, txt_img, data);
		data.x--;
		vars->r_x = vars->player_x + (vars->size / 6);
		vars->r_y = vars->player_y + (vars->size / 6);
		j += fov;
	}
}
