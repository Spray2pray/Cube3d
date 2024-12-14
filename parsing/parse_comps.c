/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_comps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisalah <louisalah@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:23:15 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/12/13 19:10:50 by louisalah        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*str_after_space(char *str)
{
	while (str && *str && *str == ' ')
		str++;
	while (str && *str && *str != ' ')
		str++;
	while (str && *str && *str == ' ')
		str++;
	return (str);
}

static int	validate_comps(t_vars *vars)
{
	if (!vars->no || !vars->so || !vars->we || !vars->ea)
		return (1);
	return (0);
}

int	read_map(t_vars *vars, char *file)
{
	int		fd;
	int		flag[6];
	char	*line;
	char	**str;
	int		flag_f;

	flag_f = 0;
	init_flags(flag);
	line = NULL;
	str = NULL;
	vars->map_fd = open(file, O_RDONLY);
	printf("map_fd = %s\n", file);
	fd = vars->map_fd;
	if (fd < 0)
		(write(2, "Failed to open file\n", 20), exit(1));
	line = get_next_line(fd);
	while (line)
	{
		if (check_map_start(line) == 1)
		{
			free_double(str, NULL);
			flag_f = 1;
			break ;
		}
		free_double(str, NULL);
		str = ft_split(line, ' ');
		if (str && str[0] && ft_strncmp(str[0], "NO", 3) == 0)
		{
			if (flag[0] == 0 && ++flag[0])
				vars->no = ft_strdup(str_after_space(line));
			else
				return (free_double(str, line), 1);
		}
		else if (str && str[0] && ft_strncmp(str[0], "SO", 3) == 0)
		{
			if (flag[1] == 0 && ++flag[1])
				vars->so = ft_strdup(str_after_space(line));
			else
				return (free_double(str, line), 1);
		}
		else if (str && str[0] && ft_strncmp(str[0], "WE", 3) == 0)
		{
			if (flag[2] == 0 && ++flag[2])
				vars->we = ft_strdup(str_after_space(line));
			else
				return (free_double(str, line), 1);
		}
		else if (str && str[0] && ft_strncmp(str[0], "EA", 3) == 0)
		{
			if (flag[3] == 0 && ++flag[3])
				vars->ea = ft_strdup(str_after_space(line));
			else
				return (free_double(str, line), 1);
		}
		else if (str && str[0] && ft_strncmp(str[0], "F", 2) == 0)
		{
			if (flag[4] || parse_floor(vars, line) == 1)
				return (free_double(str, line), 3);
			flag[4] += 1;
		}
		else if (str && str[0] && ft_strncmp(str[0], "C", 2) == 0)
		{
			if (flag[5] || parse_ceiling(vars, line) == 1)
				return (free_double(str, line), 4);
			flag[5] += 1;
		}
		else if (str && str[0])
			return (free_double(str, line), 1);
		free(line);
		line = get_next_line(fd);
	}
	if (validate_comps(vars) == 1)
	{
		if (flag_f == 1)
			return (free_double(NULL, line), 6);
		else
			return (free_double(str, line), 1);
	}
	if (flag[0] != 1 || flag[1] != 1 || flag[2] != 1 || flag[3] != 1
		|| flag[4] != 1 || flag[5] != 1)
		return (free_double(NULL, line), 1);
	if (filling_map(vars, line, fd) == 1)
		return (7);
	close(fd);
	return (0);
}
