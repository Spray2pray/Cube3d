/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbamatra <mbamatra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 13:14:18 by mbamatra          #+#    #+#             */
/*   Updated: 2024/11/27 14:17:13 by mbamatra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int					sign;
	long long			result;
	int					flag;

	flag = 0;
	result = 0;
	sign = 1;
	while (*str != '\0' && ((*str >= 9 && *str <= 13) || *str == 32))
		str++;
	if (*str == '-' || *str == '+')
		if (*(str++) == '-')
			sign = -1;
	while (*str != '\0' && (*str >= '0' && *str <= '9'))
	{
		flag = 1;
		result = result * 10 + (*(str++) - '0');
		if (result > 255 || (result > 0 && sign == -1))
			return (-1);
	}
	while (*str && *str == ' ')
		str++;
	if (*str || !flag)
		return (-1);
	return (result * sign);
}
