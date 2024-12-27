/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbamatra <mbamatra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:10:42 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/12/27 21:28:21 by mbamatra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_map_vars(t_vars *vars, char **argv)
{
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
	vars->map = NULL;
	vars->no = NULL;
	vars->so = NULL;
	vars->we = NULL;
	vars->ea = NULL;
}

void	initialize_vars(t_vars *vars, char **argv)
{
	init_map_vars(vars, argv);
	vars->size = 200;
	vars->angle = -1;
	vars->north = NULL;
	vars->south = NULL;
	vars->west = NULL;
	vars->east = NULL;
	vars->key_a = 0;
	vars->key_d = 0;
	vars->key_s = 0;
	vars->key_w = 0;
	vars->key_left = 0;
	vars->key_right = 0;
}

void	init_flags(int *flag, t_vars *vars, char *file, int *fd)
{
	vars->map_fd = open(file, O_RDONLY);
	*fd = vars->map_fd;
	if (fd < 0)
		(write(2, "Failed to open file\n", 20), exit(1));
	flag[0] = 0;
	flag[1] = 0;
	flag[2] = 0;
	flag[3] = 0;
	flag[4] = 0;
	flag[5] = 0;
	flag[6] = 0;
}

int	check_if_flag(int *flag)
{
	if ((flag[0] != 1 || flag[1] != 1 || flag[2] != 1 || flag[3] != 1
			|| flag[4] != 1 || flag[5] != 1 || flag[6] != 1))
		return (1);
	return (0);
}
