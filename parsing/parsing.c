/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounadi05 <mounadi2015@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:09:51 by ytaya             #+#    #+#             */
/*   Updated: 2022/11/06 06:02:50 by mounadi05        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double convert(int n)
{
	if (n ==  0)
		return 0.0;
	if (n == 90)
		return 3.14159;
	if (n == 270)
		return 1.5708;
	return 4.71239;

}

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
				result->view = convert(result->p_direction);
				printf("%f\n",result->p_x);
				printf("%f\n",result->p_x);
				
				ft_main(result);
			}
			else
				printf("Map is not valid\n");
		}
		else
			printf("Error\n");
		close(fd);
	}
	return (result);
}
