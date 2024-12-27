/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:17:15 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/12/27 17:18:57 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_put_pixel(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	my_mlx_pixel_get(t_img *img, int x, int y)
{
	char	*dst;
	int		color;

	color = 0;
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return (color);
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	color = (*(unsigned int *)dst);
	return (color);
}
