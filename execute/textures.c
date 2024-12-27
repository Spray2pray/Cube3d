/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 18:14:49 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/12/27 18:15:55 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_img	*get_texture_img(t_vars *vars)
{
	if (vars->hit_type == 'V')
	{
		if (vars->ray_angle >= 90 && vars->ray_angle <= 270)
			return (vars->west);
		return (vars->east);
	}
	if (vars->ray_angle >= 0 && vars->ray_angle <= 180)
		return (vars->north);
	return (vars->south);
}

float	get_texture_x(t_vars *vars, t_img *txt_img)
{
	if (vars->hit_type == 'V')
		return (((float)((int)vars->r_y % vars->size) / vars->size)
			* txt_img->width);
	return (((float)((int)vars->r_x % vars->size) / vars->size)
		* txt_img->width);
}
