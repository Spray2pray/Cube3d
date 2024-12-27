/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:11:18 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/12/27 17:35:08 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	draw_splited_screen(t_vars *vars)
{
	int	i;
	int	j;
	int	c;
	int	f;

	i = -1;
	c = rgb_to_hex(vars->ceiling_colors[0], vars->ceiling_colors[1],
			vars->ceiling_colors[2]);
	f = rgb_to_hex(vars->floor_color[0], vars->floor_color[1],
			vars->floor_color[2]);
	while (++i < 1080)
	{
		j = -1;
		while (++j < 1080)
		{
			if (i < 500)
				my_put_pixel(vars, j, i, c);
			else
				my_put_pixel(vars, j, i, f);
		}
	}
}

void	render(t_vars *vars)
{
	ft_memset(vars->addr, 0, vars->line_length * 1080);
	draw_splited_screen(vars);
	draw_cursor(vars, vars->angle, 60.0 / 1080);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img, 0, 0);
}

int	draw(t_vars *vars)
{
	ft_handle_keys(vars);
	return (0);
}
