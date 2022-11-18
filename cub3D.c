/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 20:03:45 by ytaya             #+#    #+#             */
/*   Updated: 2022/11/18 02:37:37 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

#define RED "\033[0;31m"
#define RESET "\033[0m"

void	printf_error(char *str)
{
	printf(RED "Error : %s\n" RESET, str);
	exit(1);
}

void	map_free(t_mapinfo *map)
{
	int	i;

	i = 0;
	if (map)
	{
		free(map->no);
		free(map->so);
		free(map->we);
		free(map->ea);
		free(map->f);
		free(map->c);
		if (map->map)
		{
			while (i[map->map])
			{
				free(i[map->map]);
				i++;
			}
			free(map->map);
		}
		free(map);
	}
}

int	main(int argc, char **argv)
{
	t_mapinfo	*map;

	if (argc == 2)
	{
		map = map_parse(1 [argv]);
		map_free(map);
	}
	else
	{
		printf_error("no map entered!");
		return (1);
	}
	return (0);
}
