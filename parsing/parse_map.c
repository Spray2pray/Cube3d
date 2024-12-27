/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbamatra <mbamatra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:17:08 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/12/27 21:23:38 by mbamatra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	set_player_pos(t_vars *vars, int i, int j)
{
	vars->player_x = j * vars->size + vars->size / 3;
	vars->player_y = i * vars->size + vars->size / 3;
	if (vars->map[i][j] == 'N')
		vars->angle = 90;
	else if (vars->map[i][j] == 'S')
		vars->angle = 270;
	else if (vars->map[i][j] == 'W')
		vars->angle = 180;
	else if (vars->map[i][j] == 'E')
		vars->angle = 0;
	vars->map[i][j] = '0';
}

int	validate_characters(t_vars *vars)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	i = -1;
	while (++i < vars->map_height)
	{
		j = -1;
		while (++j < (int)ft_strlen(vars->map[i]))
		{
			if (vars->map[i][j] != '0' && vars->map[i][j] != '1'
				&& vars->map[i][j] != ' ')
			{
				if (check_for_player(vars->map[i][j]))
					(set_player_pos(vars, i, j), flag++);
				else
					return (1);
			}
		}
	}
	if (flag != 1)
		return (2);
	return (0);
}

int	check_if_empty(t_vars *vars, char *line, int fd)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	while (line)
	{
		if (flag && *line != '\0')
			i++;
		else
			flag = 0;
		free(line);
		line = get_next_line(fd);
		if (!flag && line && *line != '\0')
			return (free_double(NULL, line), 1);
	}
	if (i == 0)
		return (1);
	vars->map = malloc((i + 1) * sizeof(char *));
	if (!vars->map)
		return (1);
	close(fd);
	return (0);
}

int	fill(t_vars *vars, char *line, int fd, int i)
{
	check_if_empty(vars, line, fd);
	fd = open(vars->map_name, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (check_map_start(line) == 1)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		if (*line == '\0')
		{
			free(line);
			break ;
		}
		vars->map[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	vars->map_height = i;
	vars->map[i] = NULL;
	return (0);
}
