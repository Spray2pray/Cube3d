/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisalah <louisalah@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:36:02 by mbamatra          #+#    #+#             */
/*   Updated: 2024/12/25 15:31:46 by louisalah        ###   ########.fr       */
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

void	get_text_address(t_vars *vars)
{
	vars->north->addr = mlx_get_data_addr(vars->north->img,
			&vars->north->bits_per_pixel, &vars->north->line_length,
			&vars->north->endian);
	vars->south->addr = mlx_get_data_addr(vars->south->img,
			&vars->south->bits_per_pixel, &vars->south->line_length,
			&vars->south->endian);
	vars->west->addr = mlx_get_data_addr(vars->west->img,
			&vars->west->bits_per_pixel, &vars->west->line_length,
			&vars->west->endian);
	vars->east->addr = mlx_get_data_addr(vars->east->img,
			&vars->east->bits_per_pixel, &vars->east->line_length,
			&vars->east->endian);
}
int	get_textures(t_vars *vars)
{
	vars->north = (t_img *)malloc(sizeof(t_img));
	vars->south = (t_img *)malloc(sizeof(t_img));
	vars->west = (t_img *)malloc(sizeof(t_img));
	vars->east = (t_img *)malloc(sizeof(t_img));
	if (!vars->north || !vars->south || !vars->west || !vars->east)
		return (1);
	vars->north->img = mlx_xpm_file_to_image(vars->mlx, vars->no,
			&vars->north->width, &vars->north->height);
	vars->south->img = mlx_xpm_file_to_image(vars->mlx, vars->so,
			&vars->south->width, &vars->south->height);
	vars->west->img = mlx_xpm_file_to_image(vars->mlx, vars->we,
			&vars->west->width, &vars->west->height);
	vars->east->img = mlx_xpm_file_to_image(vars->mlx, vars->ea,
			&vars->east->width, &vars->east->height);
	if (!vars->north->img || !vars->south->img || !vars->west->img
		|| !vars->east->img)
		return (1);
	get_text_address(vars);
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
	if (get_textures(&vars))
		return (write(2, "Error\nError With The Textures\n", 30), free_all(&vars), 1);
	mlx_hook(vars.mlx_win, 2, 0, ft_key_press, &vars); 
	mlx_hook(vars.mlx_win, 3, 0, ft_key_release, &vars);
	mlx_hook(vars.mlx_win, 17, 0, ft_quit, &vars);
	mlx_loop_hook(vars.mlx, draw_map2d, &vars);
	mlx_loop(vars.mlx);
}
