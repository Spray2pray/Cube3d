/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 20:25:34 by louisalah         #+#    #+#             */
/*   Updated: 2024/12/27 17:30:06 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	adjust_float_angle(float angle)
{
	if (angle >= 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	return (angle);
}

float	ft_abs(float i)
{
	if (i < 0.0)
		return (-1 * i);
	return (i);
}

int	rgb_to_hex(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
