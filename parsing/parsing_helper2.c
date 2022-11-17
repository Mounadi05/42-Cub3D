/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:17:24 by ytaya             #+#    #+#             */
/*   Updated: 2022/11/17 03:24:12 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_bool	valide_rgb(int n)
{
	return (n >= 0 && n <= 255);
}

t_token	valide_token(char *token)
{
	if (token)
	{
		if (ft_strlen(token) == 2 && !ft_strncmp(token, "NO", 2))
			return (NO);
		else if (ft_strlen(token) == 2 && !ft_strncmp(token, "SO", 2))
			return (SO);
		else if (ft_strlen(token) == 2 && !ft_strncmp(token, "WE", 2))
			return (WE);
		else if (ft_strlen(token) == 2 && !ft_strncmp(token, "EA", 2))
			return (EA);
		else if (ft_strlen(token) == 1 && !ft_strncmp(token, "F", 1))
			return (F);
		else if (ft_strlen(token) == 1 && !ft_strncmp(token, "C", 1))
			return (C);
		else
			return (BADTOKEN);
	}
	return (BADTOKEN);
}

char	*strtrim(char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i])
	{
		result[j] = str[i];
		i++;
		j++;
	}
	result[j] = 0;
	i = ft_strlen(result) - 1;
	while (result[i] == ' ' || result[i] == '\t')
	{
		result[i] = 0;
		i--;
	}
	return (result);
}

t_bool	is_empty(char *line)
{
	int	i;

	i = 0;
	if (line)
	{
		while (line[i])
		{
			if (line[i] != ' ' && line[i] != '\t')
				return (false);
			i++;
		}
		return (true);
	}
	return (false);
}

void	readmap(t_mapinfo *param, int fd)
{
	char	*line;
	char	*map;
	int		flag;

	flag = 0;
	map = strdup("");
	line = get_next_line(fd);
	while (line)
	{
		if (flag && line && !line[0])
			printf_error("invalid map!");
		if (line && !is_empty(line))
		{
			map = ft_strjoin(map, line);
			map = ft_strjoin(map, "\n");
			flag = 1;
		}
		free(line);
		line = get_next_line(fd);
	}
	param->map = ft_split(map, '\n');
	free(map);
}
