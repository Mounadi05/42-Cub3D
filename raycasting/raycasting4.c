/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 02:04:49 by ytaya             #+#    #+#             */
/*   Updated: 2022/11/18 02:34:47 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_close(t_mapinfo *result)
{
	mlx_destroy_window(result->mlx.ptr, result->mlx.win);
	exit(0);
}

void	my_mlx_pixel_put(t_mapinfo *result, int x, int y, int color)
{
	if (x >= 0 && y >= 0 && x < result->mlx.width && y < result->mlx.height)
		result->data.addr[y * result->mlx.width + x] = color;
}

void	raycasting(t_mapinfo *result)
{
	double	radius;
	double	i;
	int		in;
	int		a;

	i = result->p_direction - 0.5236;
	radius = 0;
	in = 0;
	a = 0;
	while (i < result->p_direction + 0.5236)
	{
		radius = 0;
		while (1)
		{
			if (result->map[(int)(result->p_y + sin(i) * radius)
				/ 64][(int)(result->p_x + cos(i) * radius) / 64]
				&& result->map[(int)(result->p_y + sin(i) * radius)
				/ 64][(int)(result->p_x + cos(i) * radius) / 64] != '1')
				;
			else if (result->map[(int)(result->p_y + sin(i) * (radius - 1))
				/ 64][(int)(result->p_x + cos(i) * (radius)) / 64]
					&& result->map[(int)(result->p_y + sin(i) * (radius - 1))
					/ 64][(int)(result->p_x + cos(i) * (radius)) / 64] == '1')
			{
				result->d_wall[in] = radius * cos(result->p_direction - i);
				result->w_x[in] = (int)(result->p_y + sin(i) * (radius));
				result->point_y[in] = (int)(result->p_y + sin(i) * radius) % 64;
				result->point_x[in++] = (int)(result->p_x + cos(i) * radius)
					% 64;
				break ;
			}
			else if (result->map[(int)(result->p_y + sin(i) * (radius))
				/ 64][(int)(result->p_x + cos(i) * (radius - 1)) / 64]
					&& result->map[(int)(result->p_y + sin(i) * (radius))
					/ 64][(int)(result->p_x + cos(i) * (radius - 1))
					/ 64] == '1')
			{
				result->d_wall[in] = radius * cos(result->p_direction - i);
				result->w_x[in] = (int)(result->p_x + cos(i) * (radius));
				result->point_y[in] = (int)(result->p_y + sin(i) * radius) % 64;
				result->point_x[in++] = (int)(result->p_x + cos(i) * radius)
					% 64;
				break ;
			}
			radius += 1;
		}
		i += 0.0015;
		a++;
	}
	result->len_ry = a;
	draw_wall(result);
}
