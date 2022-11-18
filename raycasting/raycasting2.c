/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounadi05 <mounadi2015@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 02:25:12 by ytaya             #+#    #+#             */
/*   Updated: 2022/11/18 03:17:08 by mounadi05        ###   ########.fr       */
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

int	draw_xmp(t_mapinfo *result, int x, int y, t_point *p)
{
	if (x % 64 < 0)
		x = 0;
	if (y % 64 < 0)
		y = 0;
	if (p->y == 0)
		return (result->add_wall_no[(y % 64) * 64 + (x % 64)]);
	else if (p->y == 63)
		return (result->add_wall_so[(y % 64) * 64 + (x % 64)]);
	else if (p->x == 0)
		return (result->add_wall_we[(y % 64) * 64 + (x % 64)]);
	else
		return (result->add_wall_ea[(y % 64) * 64 + (x % 64)]);
}

int	c_color(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

void	draw_wall(t_mapinfo *r)
{
	t_wall	w;
	t_point	p;

	w.index = -1;
	w.wall = (r->mlx.width / r->len_ry) + 1;
	while (++w.index < r->len_ry)
	{
		w.dis = (64 / floorf(r->d_wall[w.index])) * (r->mlx.height
				/ tan(0.53));
		w.max = r->mlx.height / 2 + (int)w.dis / 2 + 1;
		w.a = r->mlx.height / 2 - w.dis / 2;
		while (++w.a < r->mlx.height && w.a <= w.max)
		{
			w.y = (w.a - (r->mlx.height / 2 - (w.dis / 2) + 1))
				* (64.0 / w.dis);
			w.b = -1;
			p.x = r->point_x[w.index];
			p.y = r->point_y[w.index];
			while (++w.b < w.wall && w.b + (w.index * w.wall) < r->mlx.width)
			{
				my_mlx_pixel_put(r, w.b + (w.index * w.wall), w.a,
					draw_xmp(r, r->w_x[w.index], w.y, &p));
			}
		}
	}
}
