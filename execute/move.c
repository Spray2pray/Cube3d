/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:56:26 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/12/13 15:08:23 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_up(t_vars *vars)
{
	vars->player_y = vars->player_y - vars->size/3;
}
static void	ft_down(t_vars *vars)
{
	vars->player_y = vars->player_y + vars->size/3;
}
static void	ft_right(t_vars *vars)
{
	vars->player_x = vars->player_x + vars->size/3;
}
static void	ft_left(t_vars *vars)
{
	vars->player_x = vars->player_x - vars->size/3;
}

// static void	ft_down(t_vars *vars)
// {
// 	if (vars->vars[vars->player_y + 1][vars->player_x] != '1')
// 	{
// 		if (vars->vars[vars->player_y + 1][vars->player_x] == 'E')
// 		{
// 			if (vars->coins != 0)
// 				ft_putstr_fd("Collect all coins before exiting.\n", 2);
// 			else if (vars->coins == 0)
// 				ft_quit(vars);
// 		}
// 		else
// 		{
// 			ft_putstr_fd("your steps: ", 1);
// 			vars->steps++;
// 			ft_putnbr_fd(vars->steps, 1);
// 			ft_putchar_fd('\n', 1);
// 			vars->vars[vars->player_y][vars->player_x] = '0';
// 			vars->player_y++;
// 			vars->vars[vars->player_y][vars->player_x] = 'P';
// 		}
// 	}
// }

// static void	ft_left(t_vars *vars)
// {
// 	if (vars->vars[vars->player_y][vars->player_x - 1] != '1')
// 	{
// 		if (vars->vars[vars->player_y][vars->player_x - 1] == 'E')
// 		{
// 			if (vars->coins != 0)
// 				ft_putstr_fd("Collect all coins before exiting.\n", 2);
// 			else if (vars->coins == 0)
// 				ft_quit(vars);
// 		}
// 		else
// 		{
// 			ft_putstr_fd("your steps: ", 1);
// 			vars->steps++;
// 			ft_putnbr_fd(vars->steps, 1);
// 			ft_putchar_fd('\n', 1);
// 			vars->vars[vars->player_y][vars->player_x] = '0';
// 			vars->player_x--;
// 			vars->vars[vars->player_y][vars->player_x] = 'P';
// 		}
// 	}
// }

// static void	ft_right(t_vars *vars)
// {
// 	if (vars->vars[vars->player_y][vars->player_x + 1] != '1')
// 	{
// 		if (vars->vars[vars->player_y][vars->player_x + 1] == 'E')
// 		{
// 			if (vars->coins != 0)
// 				ft_putstr_fd("Collect all coins before exiting.\n", 2);
// 			else if (vars->coins == 0)
// 				ft_quit(vars);
// 		}
// 		else
// 		{
// 			ft_putstr_fd("your steps: ", 1);
// 			vars->steps++;
// 			ft_putnbr_fd(vars->steps, 1);
// 			ft_putchar_fd('\n', 1);
// 			vars->vars[vars->player_y][vars->player_x] = '0';
// 			vars->player_x++;
// 			vars->vars[vars->player_y][vars->player_x] = 'P';
// 		}
// 	}
// }

int	ft_move(int keycode, t_vars *vars)
{
	if (keycode == 53)
		ft_quit(vars);
	if (keycode == 13)
		ft_up(vars);
	else if (keycode == 1)
		ft_down(vars);
	else if (keycode == 0)
		ft_left(vars);
	else if (keycode == 2)
		ft_right(vars);
	return (0);
}
