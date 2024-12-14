/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisalah <louisalah@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:29:51 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/12/13 18:03:27 by louisalah        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	init_mlx(t_vars *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		printf("failed to init mlx");
		return (1);
	}
	data->mlx_win = mlx_new_window(data->mlx, 1000, 1000, "cub3d");
	if (!data->mlx_win)
	{
		printf("failed to init window");
		return (1);
	}
	
	// Create new image
	data->img = mlx_new_image(data->mlx, 1000, 1000);
	if (!data->img)
	{
		printf("failed to create image");
		return (1);
	}
	
	// Get image data
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, 
								  &data->line_length, &data->endian);
	
	return (0);
}
