/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 02:23:05 by ytaya             #+#    #+#             */
/*   Updated: 2022/11/18 02:34:47 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_main(t_mapinfo *result)
{
	result->mlx.ptr = mlx_init();
	result->mlx.height = 1000;
	result->mlx.width = 2000;
	result->mlx.win = mlx_new_window(result->mlx.ptr, result->mlx.width,
			result->mlx.height, "Cub3D");
	result->data.img = mlx_new_image(result->mlx.ptr, result->mlx.width,
			result->mlx.height);
	result->data.addr = (int *)mlx_get_data_addr(result->data.img,
			&result->data.bits_per_pixel, &result->data.line_length,
			&result->data.endian);
	init_img(result);
	mlx_hook(result->mlx.win, 2, 0, move, result);
	mlx_hook(result->mlx.win, 17, 0, ft_close, result);
	mlx_loop_hook(result->mlx.ptr, update, result);
	mlx_loop(result->mlx.ptr);
}

void	init_img(t_mapinfo *result)
{
	int	h;
	int	w;
	int	bits_per_pixel;
	int	line_length;
	int	endian;

	h = 64;
	w = 64;
	result->img_wall_no = mlx_xpm_file_to_image(result->mlx.ptr, result->no, &h,
			&w);
	result->add_wall_no = (int *)mlx_get_data_addr(result->img_wall_no,
			&bits_per_pixel, &line_length, &endian);
	result->img_wall_so = mlx_xpm_file_to_image(result->mlx.ptr, result->so, &h,
			&w);
	result->add_wall_so = (int *)mlx_get_data_addr(result->img_wall_so,
			&bits_per_pixel, &line_length, &endian);
	result->img_wall_we = mlx_xpm_file_to_image(result->mlx.ptr, result->we, &h,
			&w);
	result->add_wall_we = (int *)mlx_get_data_addr(result->img_wall_we,
			&bits_per_pixel, &line_length, &endian);
	result->img_wall_ea = mlx_xpm_file_to_image(result->mlx.ptr, result->ea, &h,
			&w);
	result->add_wall_ea = (int *)mlx_get_data_addr(result->img_wall_ea,
			&bits_per_pixel, &line_length, &endian);
}

int	move(int key, t_mapinfo *result)
{
	if (key == KEY_UP || key == KEY_W)
		up(result);
	else if (key == KEY_DOWN || key == KEY_S)
		down(result);
	else if (key == KEY_RIGHT)
		right(result);
	else if (key == KEY_LEFT)
		left(result);
	else if (key == KEY_ESC)
	{
		mlx_destroy_window(result->mlx.ptr, result->mlx.win);
		exit(0);
	}
	else if (key == KEY_A)
		move_left(result);
	else if (key == KEY_D)
		move_right(result);
	return (1);
}

void	move_left(t_mapinfo *result)
{
	if (result->map[(int)((result->p_y - 20 * sin(M_PI / 2
					+ result->p_direction)) / 64)][(int)(result->p_x - 20
			* cos(M_PI / 2 + result->p_direction)) / 64] != '1')
	{
		result->p_x -= 15 * cos(M_PI / 2 + result->p_direction);
		result->p_y -= 15 * sin(M_PI / 2 + result->p_direction);
		result->active = 1;
	}
}

void	move_right(t_mapinfo *result)
{
	if (result->map[(int)((result->p_y + 20 * sin(M_PI / 2
					+ result->p_direction)) / 64)][(int)(result->p_x + 20
			* cos(M_PI / 2 + result->p_direction)) / 64] != '1')
	{
		result->p_x += 15 * cos(M_PI / 2 + result->p_direction);
		result->p_y += 15 * sin(M_PI / 2 + result->p_direction);
		result->active = 1;
	}
}
