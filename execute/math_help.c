/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 20:25:34 by louisalah         #+#    #+#             */
/*   Updated: 2024/12/22 22:00:13 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	adjust_angle(int *angle)
{
	if (*angle >= 360)
		*angle -= 360;
	if (*angle < 0)
		*angle += 360;
}

float	ft_abs(float i)
{
	if (i < 0.0)
		return (-1 * i);
	return (i);
}