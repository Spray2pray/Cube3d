/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbamatra <mbamatra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:33:33 by mbamatra          #+#    #+#             */
/*   Updated: 2024/11/01 16:38:16 by mbamatra         ###   ########.fr       */
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

typedef struct s_floor {
	int floor_color[3];
}	t_floor;

typedef struct s_ceiling {
	int ceiling_colors[3];
}	t_ceiling;

typedef struct s_vars {
	char **map;
	char *no;
	char *so;
	char *we;
	char *ea;
	char *map_name;
	struct s_floor *floor;
	struct s_ceiling *ceiling;
	int map_height;
}	t_vars;

int validate_comps(t_vars *vars);

#endif