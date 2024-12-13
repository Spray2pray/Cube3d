/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:29:51 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/12/13 13:26:53 by asid-ahm         ###   ########.fr       */
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
	return (0);
}
