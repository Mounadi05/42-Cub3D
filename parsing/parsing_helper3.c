/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:19:29 by ytaya             #+#    #+#             */
/*   Updated: 2022/10/30 05:35:16 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_charactere(char c)
{
	if (c == ' ')
		return (1);
	if (c == '0' || c == '1'
		|| c == '2' || c == 'N'
		|| c == 'S' || c == 'W'
		|| c == 'E')
		return (1);
	return (0);
}

int	check_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!check_charactere(map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	is_space(char space)
{
	return (space != ' ' && space != '\t');
}

t_bool	read6info(t_mapinfo **param, int fd)
{
	char	*line;
	int		i;

	i = 0;
	while (i < 6)
	{
		line = get_next_line(fd);
		if (!line)
		{
			printf("Uncomplete info\n");
			return (false);
		}
		if (line && !is_empty(line))
		{
			if (getkeyvalue(param, line))
				i++;
			else
			{
				free(line);
				return (false);
			}
		}
		free(line);
	}
	return (true);
}

int	bad_token(char *value, char *key)
{
	printf("Bad token: %s\n", key);
	free(value);
	free(key);
	return (0);
}
