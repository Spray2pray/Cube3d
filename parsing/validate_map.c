/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:56:02 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/12/05 16:15:09 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

static int	surrounded_by_walls(t_vars *vars)
{
	int	i;
	int	j;

	j = -1;
	i = -1;
	while (++i < vars->map_height)
	{
		j = -1;
		while (++j < (int)ft_strlen(vars->map[i]))
		{
			if ((i == 0 || i == vars->map_height - 1)
				&& (vars->map[i][j] != '1' && vars->map[i][j] != ' '))
				return (1);
			else if ((j == 0 || j == (int)ft_strlen(vars->map[i]) - 1)
				&& (vars->map[i][j] != '1' && vars->map[i][j] != ' '))
				return (1);
		}
	}
	return (0);
}

static int	validate_zero(t_vars *vars)
{
	int	i;
	int	j;

	j = -1;
	i = -1;
	while (++i < vars->map_height)
	{
		j = -1;
		while (++j < (int)ft_strlen(vars->map[i]))
		{
			if (vars->map[i][j] == '0' || check_for_player(vars->map[i][j]))
			{
				if (j >= (int)ft_strlen(vars->map[i + 1])
					|| j >= (int)ft_strlen(vars->map[i - 1]))
					return (1);
				else if (vars->map[i][j + 1] == ' '
				|| vars->map[i][j - 1] == ' '
				|| (vars->map[i + 1][j] == ' ' || vars->map[i - 1][j] == ' '))
					return (1);
			}
		}
	}
	return (0);
}

int	check_for_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	check_map_start(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}

int	validate(t_vars *vars)
{
	if (surrounded_by_walls(vars) == 1)
		return (write(2, "Error\nMap Not Surrounded By Walls\n", 34));
	if (validate_zero(vars) == 1)
		return (write(2, "Error\nInvalid Path\n", 19));
	return (0);
}
