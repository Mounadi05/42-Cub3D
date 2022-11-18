/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:15:19 by ytaya             #+#    #+#             */
/*   Updated: 2022/11/18 02:29:47 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	int_mapinfo(t_mapinfo *param)
{
	if (param)
	{
		param->no = NULL;
		param->so = NULL;
		param->we = NULL;
		param->ea = NULL;
		param->f = NULL;
		param->c = NULL;
		param->map = NULL;
		param->p_x = -1;
		param->p_y = -1;
		param->p_direction = 4;
		param->active = 1;
		param->d_wall = malloc(1200 * 8);
		param->w_x = malloc(1200 * 8);
		param->point_y = malloc(1200 * 8);
		param->point_x = malloc(1200 * 8);
	}
}

char	*ft_toupper(char *str)
{
	int		i;
	char	*result;

	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			result[i] = str[i] - 32;
		else
			result[i] = str[i];
		i++;
	}
	result[i] = 0;
	return (result);
}

t_bool	valide_texter(char *path)
{
	return (valide_extention(path, ".XPM") == true);
}

t_bool	is_6info(t_mapinfo *param)
{
	if (param)
		return (param->no != NULL && param->so != NULL && param->we != NULL
			&& param->ea != NULL && param->f != NULL && param->c != NULL);
	return (false);
}

t_bool	is_number(char *param)
{
	int	i;

	i = 0;
	if (param)
	{
		while (param[i])
		{
			if (param[i] >= '0' && param[i] <= '9')
				i++;
			else
				return (false);
		}
		return (true);
	}
	return (false);
}
