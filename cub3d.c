/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:36:02 by mbamatra          #+#    #+#             */
/*   Updated: 2024/12/24 23:27:06 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_mapex(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	if (((file[i - 1] == 'b' && file[i - 2] == 'u')
			&& (file[i - 3] == 'c' && file[i - 4] == '.')))
		return (0);
	return (1);
}

int	all_parsing(t_vars *vars)
{
	int	i;

	i = read_map(vars, vars->map_name);
	if (i == 1)
		return (write(2, "Error\nError With The Component\n", 31));
	else if (i == 2)
		return (write(2, "Error\nError With The Map\n", 25));
	else if (i == 3)
		return (write(2, "Error\nError With The Floor Setting\n", 35));
	else if (i == 4)
		return (write(2, "Error\nError With The Ceiling Setting\n", 37));
	else if (i == 6)
		return (write(2, "Error\nFile Shouldn't Start With The Map\n", 40));
	else if (i == 7)
		return (write(2, "Error\nInvalid Map\n", 18));
	if (validate(vars))
		return (1);
	i = validate_characters(vars);
	if (i == 2)
		return (write(2, "Error\nInvalid Character\n", 24));
	else if (i == 1)
		return (write(2, "Error\nInvalid Player Count\n", 27));
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
		return (write(2, "Error\nInvalid Number of Arguments\n", 34));
	if (validate_mapex(argv[1]) == 1)
		return (write(2, "Invalid Map Extension\n", 22));
	initialize_vars(&vars, argv);
	if (all_parsing(&vars) != 0)
		return (close(vars.map_fd), free_all(&vars), 1);
	close(vars.map_fd);
	if (init_mlx(&vars))
		return (free_all(&vars), 1);
	print_comps(&vars);
	print_map(&vars);
	vars.north = (t_img *)malloc(sizeof(t_img));
	vars.north->img = mlx_xpm_file_to_image(vars.mlx, vars.no,
			&(vars.north->width), &(vars.north->height));
	vars.north->addr = mlx_get_data_addr(vars.north->img,
			&vars.north->bits_per_pixel, &vars.north->line_length,
			&vars.north->endian);
	mlx_loop_hook(vars.mlx, draw_map2d, &vars);
	mlx_hook(vars.mlx_win, 2, 0, ft_move, &vars);
	mlx_hook(vars.mlx_win, 17, 0, ft_quit, &vars);
	mlx_loop(vars.mlx);
}
