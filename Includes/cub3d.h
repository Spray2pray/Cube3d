/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbamatra <mbamatra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:33:33 by mbamatra          #+#    #+#             */
/*   Updated: 2024/11/02 23:27:18 by mbamatra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "../libft/libft.h"

typedef struct s_vars {
	char **map;
	char *no;
	char *so;
	char *we;
	char *ea;
	char *map_name;
	int floor_color[3];
	int ceiling_colors[3];
	int map_height;
	int player_x;
	int player_y;
}	t_vars;

int validate_comps(t_vars *vars);
int check_for_player(char c);
void free_double(char **map, char *str);

#endif