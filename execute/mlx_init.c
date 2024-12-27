/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbamatra <mbamatra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:29:51 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/12/27 20:46:40 by mbamatra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	get_text_address(t_vars *vars)
{
	vars->north->addr = mlx_get_data_addr(vars->north->img,
			&vars->north->bits_per_pixel, &vars->north->line_length,
			&vars->north->endian);
	vars->south->addr = mlx_get_data_addr(vars->south->img,
			&vars->south->bits_per_pixel, &vars->south->line_length,
			&vars->south->endian);
	vars->west->addr = mlx_get_data_addr(vars->west->img,
			&vars->west->bits_per_pixel, &vars->west->line_length,
			&vars->west->endian);
	vars->east->addr = mlx_get_data_addr(vars->east->img,
			&vars->east->bits_per_pixel, &vars->east->line_length,
			&vars->east->endian);
}

static int	get_textures(t_vars *vars)
{
	vars->north = (t_img *)malloc(sizeof(t_img));
	vars->south = (t_img *)malloc(sizeof(t_img));
	vars->west = (t_img *)malloc(sizeof(t_img));
	vars->east = (t_img *)malloc(sizeof(t_img));
	if (!vars->north || !vars->south || !vars->west || !vars->east)
		return (1);
	vars->north->img = mlx_xpm_file_to_image(vars->mlx, vars->no,
			&vars->north->width, &vars->north->height);
	vars->south->img = mlx_xpm_file_to_image(vars->mlx, vars->so,
			&vars->south->width, &vars->south->height);
	vars->west->img = mlx_xpm_file_to_image(vars->mlx, vars->we,
			&vars->west->width, &vars->west->height);
	vars->east->img = mlx_xpm_file_to_image(vars->mlx, vars->ea,
			&vars->east->width, &vars->east->height);
	if (!vars->north->img || !vars->south->img || !vars->west->img
		|| !vars->east->img)
		return (1);
	get_text_address(vars);
	return (0);
}

int	init_mlx(t_vars *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return ((void)printf("Error\nFailed to init mlx\n"), 1);
	if (get_textures(data))
		return ((void)printf("Error\nFailed to get textures\n"), 1);
	data->mlx_win = mlx_new_window(data->mlx, 1080, 1080, "cub3d");
	if (!data->mlx_win)
		return ((void)printf("Error\nFailed to create window\n"), 1);
	data->img = mlx_new_image(data->mlx, 1080, 1080);
	if (!data->img)
		return ((void)printf("Error\nFailed to create image\n"), 1);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	return (0);
}
