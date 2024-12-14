/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:34:52 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/12/14 19:15:45 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_comps(t_vars *vars)
{
	printf("NO: (%s)\n", vars->no);
	printf("SO: (%s)\n", vars->so);
	printf("WE: (%s)\n", vars->we);
	printf("EA: (%s)\n", vars->ea);
	printf("Floor: %d %d %d\n", vars->floor_color[0], vars->floor_color[1],
		vars->floor_color[2]);
	printf("Ceiling: %d %d %d\n", vars->ceiling_colors[0],
		vars->ceiling_colors[1], vars->ceiling_colors[2]);
}

void	print_map(t_vars *vars)
{
	int	i;

	i = 0;
	printf("players x = %f\n", vars->player_x);
	printf("players y = %f\n", vars->player_y);
	while (vars->map[i])
	{
		printf("%s\n", vars->map[i]);
		i++;
	}
}
