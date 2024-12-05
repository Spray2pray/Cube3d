/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:24:42 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/12/05 15:33:30 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

static int	array_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	count_commas(char *str)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			counter++;
		i++;
	}
	return (counter);
}

int	parse_floor(t_vars *vars, char *str)
{
	int		i;
	char	**comma_split;

	i = -1;
	while (*str == ' ')
		str++;
	str++;
	if (count_commas(str) != 2)
		return (1);
	comma_split = ft_split(str, ',');
	if (array_len(comma_split) != 3)
		return (free_double(comma_split, NULL), 1);
	if (comma_split)
	{
		while (comma_split[++i])
			vars->floor_color[i] = ft_atoi(comma_split[i]);
	}
	if (vars->floor_color[0] == -1 || vars->floor_color[1] == -1
		|| vars->floor_color[2] == -1)
		return (free_double(comma_split, NULL), 1);
	return (free_double(comma_split, NULL), 0);
}

int	parse_ceiling(t_vars *vars, char *str)
{
	int		i;
	char	**comma_split;

	i = -1;
	while (*str == ' ')
		str++;
	str++;
	if (count_commas(str) != 2)
		return (1);
	comma_split = ft_split(str, ',');
	if (array_len(comma_split) != 3)
		return (free_double(comma_split, NULL), 1);
	if (comma_split)
	{
		while (comma_split[++i])
			vars->ceiling_colors[i] = ft_atoi(comma_split[i]);
	}
	if (vars->ceiling_colors[0] == -1 || vars->ceiling_colors[1] == -1
		|| vars->ceiling_colors[2] == -1)
		return (free_double(comma_split, NULL), 1);
	return (free_double(comma_split, NULL), 0);
}
