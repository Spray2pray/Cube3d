/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbamatra <mbamatra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 13:14:18 by mbamatra          #+#    #+#             */
/*   Updated: 2024/10/28 22:04:18 by mbamatra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int					result;

	result = 0;
	while (*str != '\0' && ((*str >= 9 && *str <= 13) || *str == 32))
		str++;
	if (!*str)
		return (-1);
	if (*str == '-' || *str == '+')
		if (*(str++) == '-')
			return (-1);
	while (*str != '\0')
	{
		if (*str == ' ')
		{
			while (*str == ' ')
				str++;
			if (*str)
				return (-1);
			break ;
		}
		result = result * 10 + (*(str) - '0');
		if ((!ft_isdigit(*str++)) || result > 255)
			return (-1);
	}
	return (result);
}
