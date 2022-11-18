/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 02:25:12 by ytaya             #+#    #+#             */
/*   Updated: 2022/11/18 02:34:47 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_nowall(t_mapinfo *result)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < result->mlx.height / 2)
	{
		j = 0;
		while (j < result->mlx.width)
		{
			my_mlx_pixel_put(result, j, i, result->ceil);
			j++;
		}
		i++;
	}
}

void	draw_flor(t_mapinfo *result)
{
	int	i;
	int	j;

	i = result->mlx.height / 2;
	while (i < result->mlx.height)
	{
		j = 0;
		while (j < result->mlx.width)
		{
			my_mlx_pixel_put(result, j, i, result->floor);
			j++;
		}
		i++;
	}
}

int	draw_xmp(t_mapinfo *result, int x, int y, double v_x, double v_y)
{
	if (x % 64 < 0)
		x = 0;
	if (y % 64 < 0)
		y = 0;
	if (v_y == 0)
		return (result->add_wall_no[(y % 64) * 64 + (x % 64)]);
	else if (v_y == 63)
		return (result->add_wall_so[(y % 64) * 64 + (x % 64)]);
	else if (v_x == 0)
		return (result->add_wall_we[(y % 64) * 64 + (x % 64)]);
	else
		return (result->add_wall_ea[(y % 64) * 64 + (x % 64)]);
}

int	c_color(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

void	draw_wall(t_mapinfo *result)
{
	double	dis;
	int		index;
	int		y;
	int		wall;
	int		max;

	index = 0;
	wall = (result->mlx.width / result->len_ry) + 1;
	while (index < result->len_ry)
	{
		dis = (64 / floorf(result->d_wall[index])) * (result->mlx.height
				/ tan(0.53));
		max = result->mlx.height / 2 + (int)dis / 2 + 1;
		for (int a = result->mlx.height / 2 - dis / 2
				+ 1; a < result->mlx.height && a <= max; a++)
		{
			y = (a - (result->mlx.height / 2 - (dis / 2) + 1)) * (64.0 / dis);
			for (int b = 0; b < wall && b + (index
						* wall) < result->mlx.width; b++)
				my_mlx_pixel_put(result, b + (index * wall), a, draw_xmp(result,
							result->w_x[index], y, result->point_x[index],
							result->point_y[index]));
		}
		index++;
	}
}
