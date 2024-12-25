/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisalah <louisalah@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 20:25:34 by louisalah         #+#    #+#             */
/*   Updated: 2024/12/26 01:25:17 by louisalah        ###   ########.fr       */
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