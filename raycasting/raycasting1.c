/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 02:24:11 by ytaya             #+#    #+#             */
/*   Updated: 2022/11/18 02:34:47 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	up(t_mapinfo *result)
{
	if (result->map[(int)(result->p_y + 25 * sin(result->p_direction))
		/ 64][(int)(result->p_x + 25 * cos(result->p_direction)) / 64] != '1')
	{
		result->active = 1;
		result->p_x += 15 * cos(result->p_direction);
		result->p_y += 15 * sin(result->p_direction);
	}
}

void	down(t_mapinfo *result)
{
	if (result->map[(int)((result->p_y - 25 * sin(result->p_direction))
			/ 64)][(int)(result->p_x - 25 * cos(result->p_direction))
		/ 64] != '1')
	{
		result->active = 1;
		result->p_x -= 15 * cos(result->p_direction);
		result->p_y -= 15 * sin(result->p_direction);
	}
}

void	right(t_mapinfo *result)
{
	result->p_direction += 0.15;
	result->active = 1;
}

void	left(t_mapinfo *result)
{
	result->p_direction -= 0.15;
	result->active = 1;
}

int	update(t_mapinfo *result)
{
	if (result->active)
	{
		result->active = 0;
		mlx_destroy_image(result->mlx.ptr, result->data.img);
		mlx_clear_window(result->mlx.ptr, result->mlx.win);
		result->data.img = mlx_new_image(result->mlx.ptr, result->mlx.width,
				result->mlx.height);
		result->data.addr = (int *)mlx_get_data_addr(result->data.img,
				&result->data.bits_per_pixel, &result->data.line_length,
				&result->data.endian);
		draw_nowall(result);
		draw_flor(result);
		raycasting(result);
		mlx_put_image_to_window(result->mlx.ptr, result->mlx.win,
			result->data.img, 0, 0);
	}
	return (1);
}
