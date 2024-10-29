/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbamatra <mbamatra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:36:02 by mbamatra          #+#    #+#             */
/*   Updated: 2024/10/28 22:17:55 by mbamatra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/cub3d.h"

int count_lines(char *file)
{
	int fd;
	int i;
	char *line;

	i = 0;
	fd = open(file, O_RDONLY);
	line = NULL;
	if (fd < 0)
		(write(2, "Error opening map\n", 18), exit(1));
	line = get_next_line(fd);
	while (line)
	{
		line = get_next_line(fd);
		free(line);
		i++;
	}
	close(fd);
	return(i);
}
int check_map_start(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '1')
		return (1);
	return (0);
}

void init_flags(int *flag)
{
	flag[0] = 0;
	flag[1] = 0;
	flag[2] = 0;
	flag[3] = 0;
	flag[4] = 0;
	flag[5] = 0;
}

int array_len(char **str)
{
	int i = 0;
	while (str[i])
		i++;
	return(i);
}

int count_commas(char *str)
{
	int i = 0;
	int counter = 0;
	while (str[i])
	{
		if (str[i] == ',')
			counter++;
		i++;
	}
	return(counter);
}

char *str_after_space(char *str)
{
	while (*str == ' ')
		str++;
	while (*str != ' ')
		str++;
	while (*str == ' ')
		str++;
	return (str);
}
void parse_floor(t_vars *vars, char *str)
{
	int i;
	char **comma_split;

	i = 0;
	while (*str == ' ')
		str++;
	str++;
	if (count_commas(str) != 2)
		(write(2, "Error\nMore than 2 commas\n", 25), exit(1));
	if (*str != ' ')
		(write(2, "Invalid Component\n", 18), exit(1));
	comma_split = ft_split(str, ',');
	if (array_len(comma_split) != 3)
		(write(2, "Invalid Component\n", 18), exit(1));
	while (comma_split && comma_split[i])
	{
		vars->floor->floor_color[i] = ft_atoi(comma_split[i]);
		i++;
	}
}

void parse_ceiling(t_vars *vars, char *str)
{
	int i;
	char **comma_split;

	i = 0;
	while (*str == ' ')
		str++;
	str++;
	comma_split = ft_split(str, ',');
	if (array_len(comma_split) != 3)
		(write(2, "Invalid Component\n", 18), exit(1));
	while (comma_split && comma_split[i])
	{
		vars->ceiling->ceiling_colors[i] = ft_atoi(comma_split[i]);
		i++;
	}
}

void read_map(t_vars *vars, char *file)
{
	int fd;
	int flag[6];
	char *line;
	char **str;

	init_flags(flag);
	line = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		(write(2, "Failed to open file\n", 20), exit(1));
	line = get_next_line(fd);
	while (line)
	{
		if (check_map_start(line) == 1)
			break;
		str = ft_split(line, ' ');
		if (str && str[0] && ft_strncmp(str[0], "NO", 2) == 0)
			vars->no = str_after_space(line), flag[0] += 1;
		else if (str && str[0] && ft_strncmp(str[0], "SO", 2) == 0)
			vars->so = str_after_space(line), flag[1] += 1;
		else if (str && str[0] && ft_strncmp(str[0], "WE", 2) == 0)
			vars->we = str_after_space(line), flag[2] += 1;
		else if (str && str[0] && ft_strncmp(str[0], "EA", 2) == 0)
			vars->ea = str_after_space(line), flag[3] += 1;
		else if (str && str[0] && ft_strncmp(str[0], "F", 1) == 0)
			parse_floor(vars, line), flag[4] += 1;
		else if (str && str[0] && ft_strncmp(str[0], "C", 1) == 0)
			parse_ceiling(vars, line), flag[5] += 1;
		else if (str && str[0])
			(write(2, "Error\nInvalid Components\n", 26), exit(1));
		line = get_next_line(fd);
	}
	if (flag[0] > 1 || flag[1] > 1 || flag[2] > 1 || flag[3] > 1 
		|| flag[4] > 1 || flag[5] > 1)
		(write(2, "Error\nDuplicate Component\n", 27), exit(1));
	// vars->map_height = i;
	// vars->map[i] = NULL;
	close(fd);
	return ;
}

void print_comps(t_vars *vars)
{
	printf("NO: (%s)\n", vars->no);
	printf("SO: (%s)\n", vars->so);
	printf("WE: (%s)\n", vars->we);
	printf("EA: (%s)\n", vars->ea);
	printf("Floor: %d %d %d\n", vars->floor->floor_color[0], vars->floor->floor_color[1], vars->floor->floor_color[2]);
	printf("Ceiling: %d %d %d\n", vars->ceiling->ceiling_colors[0], vars->ceiling->ceiling_colors[1], vars->ceiling->ceiling_colors[2]);
}
// void read_map(t_vars *vars, char *file)
// {
// 	int i;
// 	int fd;
// 	char *line;

// 	line = NULL;
// 	// vars->map = malloc((count_lines(file) + 1) * sizeof(char *));
// 	// if (!vars->map)
// 	// 	return ;
// 	// i = 0;
// 	fd = open(file, O_RDONLY);
// 	if (fd < 0)
// 		(write(2, "Failed to open file\n", 20), free(vars->map), exit(1));
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		// vars->map[i++] = line;
// 		line = get_next_line(fd);
// 	}
// 	vars->map_height = i;
// 	vars->map[i] = NULL;
// 	close(fd);
// 	return ;
// }

int validate_mapex(char *file)
{
	int i = 0;
	while (file[i])
		i++;
	if (!(file[i - 1] == 'u' || file[i - 2] == 'u' 
		|| file[i - 3] == 'c' || file[i - 4] == '.'))
		return (1);
	return (0);
}

void print_map(t_vars *vars)
{
	int i = 0;
	while (vars->map[i])
	{
		printf("%s\n", vars->map[i]);
		i++;
	}
}

int validate_comps(t_vars *vars)
{
	if (!vars->no || !vars->so || !vars->we || !vars->ea)
		return (1);
	if (vars->floor->floor_color[0] == -1 || vars->floor->floor_color[1] == -1 ||
		vars->floor->floor_color[2] == -1)
		return(1);
	if (vars->ceiling->ceiling_colors[0] == -1 || vars->ceiling->ceiling_colors[1] == -1 ||
		vars->ceiling->ceiling_colors[2] == -1)
		return (1);
	return (0);
}

void initialize_vars(t_vars *vars)
{
	vars->map = NULL;
	vars->no = NULL;
	vars->so = NULL;
	vars->we = NULL;
	vars->ea = NULL;
	vars->map_height = 0;
	vars->floor = malloc(sizeof(t_floor));
	vars->ceiling = malloc(sizeof(t_ceiling));
	vars->floor->floor_color[0] = -1;
	vars->floor->floor_color[1] = -1;
	vars->floor->floor_color[2] = -1;
	vars->ceiling->ceiling_colors[0] = -1;
	vars->ceiling->ceiling_colors[1] = -1;
	vars->ceiling->ceiling_colors[2] = -1;
}

int main(int argc, char **argv)
{
	t_vars vars;
	if (argc != 2)
		return(write(2, "Error\nInvalid Number of Arguments\n", 34));
	if (validate_mapex(argv[1]) == 1)
		return(write(2, "Invalid Map Extension\n", 22));
	initialize_vars(&vars);
	read_map(&vars, argv[1]);
	if (validate_comps(&vars) == 1)
		return(write(2, "Error\nComponent Not Found\n", 27));
	print_comps(&vars);
	// if (parse_map(&vars) == 1)
	// 	return(write(2, "Error\nInvalid Map\n", 18));
	// print_map(&vars);
}

/* 
if (vars->map[i][j] == ' ' || vars->map[i][j] == '\0')
				j++;
			if (ft_strncmp(vars->map[i], "NO ", 3) == 0)
				printf("NO\n");
			else if (ft_strncmp(vars->map[i], "SO ", 3) == 0)
				printf("SO\n");
			else if (ft_strncmp(vars->map[i], "WE ", 3) == 0)
				printf("WE\n");
			else if (ft_strncmp(vars->map[i], "EA ", 3) == 0)
				printf("EA\n");
			else if (ft_strncmp(vars->map[i], "F ", 2) == 0)
				printf("F\n");
			else if (ft_strncmp(vars->map[i], "C ", 2) == 0)
				printf("C\n");
			else if (vars->map[i][j] == '1' || vars->map[i][j] == '0')
				printf("Map\n");
			else
				return (1);*/