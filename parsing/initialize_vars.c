/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:10:42 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/12/24 23:27:26 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_flags(int *flag)
{
	flag[0] = 0;
	flag[1] = 0;
	flag[2] = 0;
	flag[3] = 0;
	flag[4] = 0;
	flag[5] = 0;
}

void	initialize_vars(t_vars *vars, char **argv)
{
	vars->size = 500;
	vars->angle = -1;
	vars->map = NULL;
	vars->no = NULL;
	vars->so = NULL;
	vars->we = NULL;
	vars->ea = NULL;
	vars->map_fd = -1;
	vars->player_x = -1;
	vars->player_y = -1;
	vars->map_height = 0;
	vars->floor_color[0] = -1;
	vars->floor_color[1] = -1;
	vars->floor_color[2] = -1;
	vars->ceiling_colors[0] = -1;
	vars->ceiling_colors[1] = -1;
	vars->ceiling_colors[2] = -1;
	vars->map_name = argv[1];
}
