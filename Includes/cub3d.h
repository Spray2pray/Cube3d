/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:33:33 by mbamatra          #+#    #+#             */
/*   Updated: 2024/12/05 16:55:56 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "get_next_line.h"
# include "../libft/libft.h"

typedef struct s_vars
{
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		map_fd;
	char	*map_name;
	int		floor_color[3];
	int		ceiling_colors[3];
	int		map_height;
	int		player_x;
	int		player_y;
}	t_vars;

void	initialize_vars(t_vars *vars, char **argv);
void	init_flags(int *flag);
void	free_double(char **map, char *str);
void	free_all(t_vars *vars);
int		parse_floor(t_vars *vars, char *str);
int		parse_ceiling(t_vars *vars, char *str);
int		check_for_player(char c);
int		validate(t_vars *vars);
void	print_comps(t_vars *vars);
int		check_map_start(char *line);
int		validate_characters(t_vars *vars);
void	print_map(t_vars *vars);
int		filling_map(t_vars *vars, char *line, int fd);
int		read_map(t_vars *vars, char *file);

#endif