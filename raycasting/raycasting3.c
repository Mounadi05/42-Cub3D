/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 02:31:39 by ytaya             #+#    #+#             */
/*   Updated: 2022/11/18 02:34:47 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_color(t_mapinfo *result)
{
	result->floor = ((result->f->r & 0xff) << 16) + ((result->f->g & 0xff) << 8)
		+ (result->f->b & 0xff);
	result->ceil = ((result->c->r & 0xff) << 16) + ((result->c->g & 0xff) << 8)
		+ (result->c->b & 0xff);
}
