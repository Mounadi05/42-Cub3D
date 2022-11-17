/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounadi05 <mounadi2015@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 20:03:45 by ytaya             #+#    #+#             */
/*   Updated: 2022/11/17 00:44:03 by mounadi05        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

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
			while (map->map[i])
			{
				free(map->map[i]);
				i++;
			}
			free(map->map);
		}
	}
	free(map);	
}

int	main(int argc, char	**argv)
{
	t_mapinfo	*map;

	if (argc == 2)
	{    
		map = map_parse(argv[1]);
		map_free(map);
	}
	else
	{
		printf("no map entered!\n");
		return (1);
	}
	return (0);
}
