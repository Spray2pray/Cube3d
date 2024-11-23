/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbamatra <mbamatra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:36:02 by mbamatra          #+#    #+#             */
/*   Updated: 2024/11/14 01:52:30 by mbamatra         ###   ########.fr       */
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
	if (line[i] == '1' || line[i] == '0')
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

int validate_characters(t_vars *vars)
{
	int i;
	int j;
	int flag;

	flag = 0;
	i = -1;
	j = -1;
	while (++i < vars->map_height)
	{
		j = -1;
		while (++j < (int)ft_strlen(vars->map[i]))
		{
			if (vars->map[i][j] != '0' && vars->map[i][j] != '1' && vars->map[i][j] != ' ')
			{
				if (check_for_player(vars->map[i][j]))
				{
					vars->player_x = j;
					vars->player_y = i;
					flag++;
				}
				else
					return(1);
			}
		}
	}
	if (flag != 1)
		return(2);
	return(0);
}

int check_for_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int validate_zero(t_vars *vars)
{
	int i;
	int j;

	j = -1;
	i = -1;
	while (++i < vars->map_height)
	{
		j = -1;
		while (++j < (int)ft_strlen(vars->map[i]))
		{
			if (vars->map[i][j] == '0' || check_for_player(vars->map[i][j]))
			{
				if (j >= (int)ft_strlen(vars->map[i + 1]) || j >= (int)ft_strlen(vars->map[i - 1]))
					return(1);
				else if (vars->map[i][j + 1] == ' ' || vars->map[i][j - 1] == ' '
				|| (vars->map[i + 1][j] == ' ' || vars->map[i - 1][j] == ' '))
					return(1);
			}
		}
	}
	return(0);
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
	while (str && *str && *str == ' ')
		str++;
	while (str && *str && *str != ' ')
		str++;
	while (str && *str && *str == ' ')
		str++;
	return (str);
}
int parse_floor(t_vars *vars, char *str)
{
	int i;
	char **comma_split;

	i = 0;
	while (*str == ' ')
		str++;
	str++;
	if (count_commas(str) != 2)
		return (1);
	comma_split = ft_split(str, ',');
	if (array_len(comma_split) != 3)
	{
		printf("array len = %d\n", array_len(comma_split));
		return (free_double(comma_split, NULL), 1);
	}
	while (comma_split && comma_split[i])
	{
		vars->floor_color[i] = ft_atoi(comma_split[i]);
		i++;
	}
	if (vars->floor_color[0] == -1 || vars->floor_color[1] == -1 ||
		vars->floor_color[2] == -1)
		return(free_double(comma_split, NULL), 1);
	return(free_double(comma_split, NULL), 0);
}

int parse_ceiling(t_vars *vars, char *str)
{
	int i;
	char **comma_split;

	i = 0;
	while (*str == ' ')
		str++;
	str++;
	if (count_commas(str) != 2)
		return (1);
	comma_split = ft_split(str, ',');
	if (array_len(comma_split) != 3)
		return(free_double(comma_split, NULL), 1);
	while (comma_split && comma_split[i])
	{
		vars->ceiling_colors[i] = ft_atoi(comma_split[i]);
		i++;
	}
	if (vars->ceiling_colors[0] == -1 || vars->ceiling_colors[1] == -1 ||
		vars->ceiling_colors[2] == -1)
		return(free_double(comma_split, NULL), 1);
	return(free_double(comma_split, NULL), 0);
}


int surrounded_by_walls(t_vars *vars)
{
	int i = -1;
	int j = -1;
	while (++i < vars->map_height)
	{
		j = -1;
		while (++j < (int)ft_strlen(vars->map[i]))
		{
			if ((i == 0 || i == vars->map_height - 1) && (vars->map[i][j] != '1' && vars->map[i][j] != ' '))
				return (1);
			else if ((j == 0 || j == (int)ft_strlen(vars->map[i]) - 1) && (vars->map[i][j] != '1' && vars->map[i][j] != ' '))
				return (1);
		}
	}
	return(0);
}

int filling_map(t_vars *vars, char *line, int fd)
{
	int i = 0;
	int flag = 1;
	while (line)
	{
		if (flag && *line != '\0')
			i++;
		else
			flag = 0;
		free(line);
		line = get_next_line(fd);
		if (!flag && line && *line != '\0')
			return(free_double(NULL, line), 1);
	}
	if (i == 0)
		return (1);
	vars->map = malloc((i + 1) * sizeof(char *));
	if (!vars->map)
		return (1);
	close(fd);
	fd = open(vars->map_name, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (check_map_start(line) == 1)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	i = 0;
	while (line)
	{
		if (*line == '\0')
			break ;
		vars->map[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	vars->map_height = i;
	vars->map[i] = NULL;
	return (0);
	// printf("map_height = %d\n", vars->map_height);
}

int read_map(t_vars *vars, char *file)
{
	int fd;
	int flag[6];
	char *line;
	int flag_f = 0;
	char **str;
	int counter = 0;

	init_flags(flag);
	line = NULL;
	str = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		(write(2, "Failed to open file\n", 20), exit(1));
	line = get_next_line(fd);
	while (line)
	{
		counter++;
		if (check_map_start(line) == 1)
		{
			free_double(str, NULL);
			flag_f = 1;
			break ;
		}
		free_double(str, NULL);
		str = ft_split(line, ' ');
		if (str && str[0] && ft_strncmp(str[0], "NO", 3) == 0)
			vars->no = ft_strdup(str_after_space(line)), flag[0] += 1;
		else if (str && str[0] && ft_strncmp(str[0], "SO", 3) == 0)
			vars->so = ft_strdup(str_after_space(line)), flag[1] += 1;
		else if (str && str[0] && ft_strncmp(str[0], "WE", 3) == 0)
			vars->we = ft_strdup(str_after_space(line)), flag[2] += 1;
		else if (str && str[0] && ft_strncmp(str[0], "EA", 3) == 0)
			vars->ea = ft_strdup(str_after_space(line)), flag[3] += 1;
		else if (str && str[0] && ft_strncmp(str[0], "F", 2) == 0)
		{
			flag[4] += 1;
			if (parse_floor(vars, line) == 1)
				return(free_double(str, line), 3);
		}
		else if (str && str[0] && ft_strncmp(str[0], "C", 2) == 0)
		{
			flag[5] += 1;
			if (parse_ceiling(vars, line) == 1)
				return(free_double(str, line), 4);
		}
		else if (str && str[0])
			return(free_double(str, line), 1);
		free(line);
		line = get_next_line(fd);
	}
	counter = validate_comps(vars);
	if (counter == 1 && flag_f == 1)
		return(free_double(NULL, line), 6);
	else if (counter == 1 && flag_f == 0)
		return(free_double(str, line), 1);
	if (flag[0] != 1 || flag[1] != 1 || flag[2] != 1 || flag[3] != 1 
		|| flag[4] != 1 || flag[5] != 1)
			return(free_double(NULL, line), 1);
	if (filling_map(vars, line, fd) == 1)
		return(3);
	// vars->map_height = i;
	// vars->map[i] = NULL;
	close(fd);
	return (0);
}

void print_comps(t_vars *vars)
{
	printf("NO: (%s)\n", vars->no);
	printf("SO: (%s)\n", vars->so);
	printf("WE: (%s)\n", vars->we);
	printf("EA: (%s)\n", vars->ea);
	printf("Floor: %d %d %d\n", vars->floor_color[0], vars->floor_color[1], vars->floor_color[2]);
	printf("Ceiling: %d %d %d\n", vars->ceiling_colors[0], vars->ceiling_colors[1], vars->ceiling_colors[2]);
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
	if ((file[i - 1] == 'b' && file[i - 2] == 'u' 
		&& file[i - 3] == 'c' && file[i - 4] == '.'))
		return (0);
	return (1);
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
	return (0);
}

void initialize_vars(t_vars *vars, char **argv)
{
	vars->map = NULL;
	vars->no = NULL;
	vars->so = NULL;
	vars->we = NULL;
	vars->ea = NULL;
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

int all_parsing(t_vars *vars)
{
	int i;

	i = read_map(vars, vars->map_name);
	if (i == 1)
		return(write(2, "Error\nError With The Component\n", 31));
	else if (i == 2)
		return(write(2, "Error\nError With The Map\n", 25));
	else if (i == 3)
		return(write(2, "Error\nError With The Floor Setting\n", 35));	
	else if (i == 4)
		return(write(2, "Error\nError With The Ceiling Setting\n", 37));
	else if (i == 6)
		return(write(2, "Error\nFile Shouldn't Start With The Map\n", 40));
	if (validate_comps(vars) == 1)
		return(write(2, "Error\nError With The Components\n", 32));
	if (surrounded_by_walls(vars) == 1)
		return(write(2, "Error\nMap Not Surrounded By Walls\n", 34));
	if (validate_zero(vars) == 1)
		return(write(2, "Error\nInvalid Path\n", 19));
	i = validate_characters(vars);
	if (i == 2)
		return(write(2, "Error\nInvalid Character\n", 24));
	else if (i == 1)
		return(write(2, "Error\nInvalid Player Count\n", 27));
	// else if (i == 3)
	// 	return(write(2, "Error\nInvalid Path\n", 19));
	return(0);
}

void free_double(char **map, char *str)
{
	int i;

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

void free_all(t_vars *vars)
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
	
}



int main(int argc, char **argv)
{
	t_vars vars;
	if (argc != 2)
		return(write(2, "Error\nInvalid Number of Arguments\n", 34));
	if (validate_mapex(argv[1]) == 1)
		return(write(2, "Invalid Map Extension\n", 22));
	initialize_vars(&vars, argv);
	if (all_parsing(&vars) != 0)
		return(free_all(&vars), 1);
	print_comps(&vars);
	print_map(&vars);
}
