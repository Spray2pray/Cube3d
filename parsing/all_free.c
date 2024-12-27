/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbamatra <mbamatra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:29:18 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/12/27 20:17:01 by mbamatra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_double(char **map, char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		free(str);
		str = NULL;
	}
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	map = NULL;
}

void	free_all(t_vars *vars)
{
	if (vars->map)
		free_double(vars->map, NULL);
	if (vars->no)
		free(vars->no);
	if (vars->so)
		free(vars->so);
	if (vars->we)
		free(vars->we);
	if (vars->ea)
		free(vars->ea);
	if (vars->north)
		free(vars->north);
	if (vars->south)
		free(vars->south);
	if (vars->west)
		free(vars->west);
	if (vars->east)
		free(vars->east);
}

int	ft_quit(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	free_all(vars);
	exit(0);
}
