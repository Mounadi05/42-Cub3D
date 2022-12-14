/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:09:51 by ytaya             #+#    #+#             */
/*   Updated: 2022/11/18 02:30:31 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static t_bool	valide_extention_free(char *prt, t_bool flag)
{
	free(prt);
	return (flag);
}

t_bool	valide_extention(char *filename, char *extention)
{
	char	*tmp;
	char	*file;
	int		fd;

	file = ft_toupper(filename);
	if (!filename)
		return (valide_extention_free(file, false));
	fd = open(filename, O_RDONLY);
	close(fd);
	if (fd < 0)
		return (valide_extention_free(file, false));
	tmp = ft_strrchr(file, '.');
	if (tmp)
	{
		if (!ft_strncmp(tmp, extention, ft_strlen(extention)))
			return (valide_extention_free(file, true));
	}
	return (valide_extention_free(file, false));
}

int	valid_map(char **map)
{
	int	i;
	int	j;
	int	maphight;

	i = 0;
	maphight = 0;
	while (map[maphight])
		maphight++;
	if (check_map(map))
	{
		while (map[i])
		{
			j = 0;
			while (map[i][j])
			{
				if (map[i][j] == '0')
					if (!valid(map, j, i, maphight))
						return (0);
				j++;
			}
			i++;
		}
		return (1);
	}
	return (0);
}

int	valid(char **map, int j, int i, int maphight)
{
	int	len;

	len = ft_strlen(map[i]) - 1;
	if (i == 0 || j == 0 || i == maphight || j == len)
		return (0);
	if (i == maphight - 1)
		return (0);
	if (map[i - 1][j] == ' ' || map[i - 1][j] == '\0')
		return (0);
	if (map[i + 1][j] == ' ' || map[i + 1][j] == '\0')
		return (0);
	if (map[i][j + 1] == ' ' || map[i][j + 1] == '\0')
		return (0);
	if (map[i][j - 1] == ' ' || map[i][j - 1] == '\0')
		return (0);
	return (1);
}

t_mapinfo	*map_parse(char *filename)
{
	t_mapinfo	*result;
	int			fd;

	result = NULL;
	if (valide_extention(filename, ".CUB"))
	{
		result = malloc(sizeof(t_mapinfo));
		int_mapinfo(result);
		fd = open(filename, O_RDONLY);
		if (read6info(&result, fd) && is_6info(result))
		{
			readmap(result, fd);
			if (valid_map(result->map) && check_player(&result))
			{
				ft_color(result);
				ft_main(result);
			}
			else
				printf_error("invalid map");
		}
		close(fd);
	}
	else
		printf_error("invalid extention");
	return (result);
}
