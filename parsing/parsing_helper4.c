/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounadi05 <mounadi2015@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:38:17 by ytaya             #+#    #+#             */
/*   Updated: 2022/11/13 06:16:06 by mounadi05        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static	int	count_commas(char *line)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == ',')
			n++;
		i++;
	}
	return (n);
}

static void	ft_free1(char **arr)
{
	int	j;

	j = 0;
	while (arr[j])
	{
		free(arr[j]);
		j++;
	}
	free(arr);
}

static void	init_color(int i, t_color *color, char **arr)
{
	if (i == 0)
	(color)->r = ft_atoi(arr[i]);
	else if (i == 1)
	(color)->g = ft_atoi(arr[i]);
	else
	(color)->b = ft_atoi(arr[i]);
}

static t_color	*valide_color_helper(int i, t_color *color)
{
	if (i != 3)
		return (NULL);
	return (color);
}

t_color	*is_valide_color(char *param)
{
	t_color	*color;
	char	**arr;
	int		i;
	int		n;

	i = 0;
	n = count_commas(param);
	if (param && n == 2)
	{
		color = malloc(sizeof(t_color));
		arr = ft_split(param, ',');
		while (arr[i])
		{
			if (is_number(arr[i]) && valide_rgb(ft_atoi(arr[i])))
			{
				init_color(i, color, arr);
				i++;
			}
			else
				break ;
		}
		ft_free1(arr);
		return (valide_color_helper(i, color));
	}
	return (NULL);
}
