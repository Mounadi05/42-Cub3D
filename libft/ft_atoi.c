/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:27:02 by ytaya             #+#    #+#             */
/*   Updated: 2022/10/29 20:19:18 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	ft_trinary(t_bool check, int t, int f)
{
	if (check)
		return (t);
	return (f);
}

int	ft_atoi(const char *nptr)
{
	unsigned long long			number;
	int							sign;
	int							i;
	int							n;

	i = 0;
	sign = 1;
	number = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			sign = -1;
	n = i;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		number = number * 10 + (nptr[i++] - 48);
	if (i - n <= 19 && number <= LLONG_MAX)
		return (((int)number) * sign);
	return (ft_trinary(sign < 0, 0, -1));
}
