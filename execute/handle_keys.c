/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:05:09 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/12/27 17:05:30 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_handle_keys(t_vars *vars)
{
	if (vars->key_w)
		ft_decide_direction(vars, 1);
	if (vars->key_s)
		ft_decide_direction(vars, 2);
	if (vars->key_a)
		ft_decide_direction(vars, 3);
	if (vars->key_d)
		ft_decide_direction(vars, 4);
	if (vars->key_right)
	{
		vars->angle -= 10;
		while (vars->angle >= 360)
			vars->angle -= 360;
	}
	if (vars->key_left)
	{
		vars->angle += 10;
		while (vars->angle < 0)
			vars->angle += 360;
	}
	render(vars);
	return (0);
}
