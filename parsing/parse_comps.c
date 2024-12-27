/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_comps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbamatra <mbamatra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 19:40:24 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/12/27 21:28:33 by mbamatra         ###   ########.fr       */
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

int	assign_textures(char **str, int *flag, t_vars *vars, char *line)
{
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
	else
		return (2);
	return (0);
}

int	assign_comp(char **str, int *flag, t_vars *vars, char *line)
{
	int	i;

	i = assign_textures(str, flag, vars, line);
	if (i == 1)
		return (1);
	else if (str && str[0] && ft_strncmp(str[0], "EA", 3) == 0)
	{
		if (flag[3] == 0 && ++flag[3])
			vars->ea = ft_strdup(str_after_space(line));
		else
			return (free_double(str, line), 1);
	}
	else if (str && str[0] && ft_strncmp(str[0], "F", 2) == 0)
	{
		if (flag[4]++ || parse_floor(vars, line) == 1)
			return (free_double(str, line), 3);
	}
	else if (str && str[0] && ft_strncmp(str[0], "C", 2) == 0)
	{
		if (flag[5]++ || parse_ceiling(vars, line) == 1)
			return (free_double(str, line), 4);
	}
	else if (i == 2 && str && str[0])
		return (free_double(str, line), 1);
	return (0);
}

int	read_map(t_vars *vars, char *file, char **str, char *line)
{
	int		fd;
	int		flag[7];

	init_flags(flag, vars, file, &fd);
	line = get_next_line(fd);
	while (line)
	{
		if (check_map_start(line) == 1)
		{
			flag[6]++;
			break ;
		}
		free_double(str, NULL);
		str = ft_split(line, ' ');
		if (assign_comp(str, flag, vars, line))
			return (close(fd), 1);
		free(line);
		line = get_next_line(fd);
	}
	if (validate_comps(vars) == 1)
		return (free_double(str, line), 1);
	if (check_if_flag(flag) || (fill(vars, line, fd, 0) == 1))
		return (free_double(NULL, line), 1);
	return (close(fd), 0);
}
