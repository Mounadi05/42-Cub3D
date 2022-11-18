/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounadi05 <mounadi2015@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 02:04:49 by ytaya             #+#    #+#             */
/*   Updated: 2022/11/18 03:42:12 by mounadi05        ###   ########.fr       */
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

static	int	ft_norm(t_mapinfo *r, double *ra, double *i, int *in)
{
	if (r->map[(int)(r->p_y + sin(*i) * (*ra - 1))
		/ 64][(int)(r->p_x + cos(*i) * *ra) / 64]
			&& r->map[(int)(r->p_y + sin(*i) * (*ra - 1))
			/ 64][(int)(r->p_x + cos(*i) * *ra) / 64] == '1')
	{
		r->d_wall[*in] = *ra * cos(r->p_direction - *i);
		r->w_x[*in] = (int)(r->p_y + sin(*i) * *ra);
		r->point_y[*in] = (int)(r->p_y + sin(*i) * *ra) % 64;
		r->point_x[(*in)++] = (int)(r->p_x + cos(*i) * *ra) % 64;
		return (0);
	}
	else if (r->map[(int)(r->p_y + sin(*i) * (*ra))
		/ 64][(int)(r->p_x + cos(*i) * (*ra - 1)) / 64]
			&& r->map[(int)(r->p_y + sin(*i) * *ra) / 64]
			[(int)(r->p_x + cos(*i) * (*ra - 1)) / 64] == '1')
	{
		r->d_wall[*in] = *ra * cos(r->p_direction - *i);
		r->w_x[*in] = (int)(r->p_x + cos(*i) * *ra);
		r->point_y[*in] = (int)(r->p_y + sin(*i) * *ra) % 64;
		r->point_x[(*in)++] = (int)(r->p_x + cos(*i) * *ra) % 64;
		return (0);
	}
	return (1);
}

void	raycasting(t_mapinfo *r)
{
	double	ra;
	double	i;
	int		in;

	i = r->p_direction - 0.5236;
	in = 0;
	r->len_ry = 0;
	while (i < r->p_direction + 0.5236)
	{
		ra = 0;
		while (1)
		{
			if (r->map[(int)(r->p_y + sin(i) * ra)
				/ 64][(int)(r->p_x + cos(i) * ra) / 64]
			&& r->map[(int)(r->p_y + sin(i) * ra)
				/ 64][(int)(r->p_x + cos(i) * ra) / 64] != '1');
			else if (!ft_norm(r, &ra, &i, &in))
				break ;
			ra += 1;
		}
		i += 0.0015;
		r->len_ry++;
	}
	draw_wall(r);
}
