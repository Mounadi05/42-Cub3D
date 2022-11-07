/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:28:08 by ytaya             #+#    #+#             */
/*   Updated: 2022/10/30 05:21:30 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	handel_ea(char *value, t_mapinfo **param)
{
	if (valide_texter(value) && !(*param)->ea)
	{
		(*param)->ea = value;
	}
	else
		printf("Error in EA\n");
}

void	handel_f(char *value, t_mapinfo **param)
{
	t_color	*tmp1;

	tmp1 = is_valide_color(value);
	if (tmp1 && !(*param)->f)
	{
		(*param)->f = tmp1;
		free(value);
	}
	else
		printf("Error in F\n");
}

void	handel_c(char *value, t_mapinfo **param)
{
	t_color	*tmp1;

	tmp1 = is_valide_color(value);
	if (tmp1 && !(*param)->c)
	{
		(*param)->c = tmp1;
		free(value);
	}
	else
		printf("Error in C\n");
}

static t_bool	init_player(t_mapinfo **param, int i, int j)
{
	if ((*param)->map[i][j] == 'N'
	|| (*param)->map[i][j] == 'S'
	|| (*param)->map[i][j] == 'W'
	|| (*param)->map[i][j] == 'E')
	{
		(*param)->p_x = j * TAILSIZE + TAILSIZE / 2;
		(*param)->p_y = i * TAILSIZE + TAILSIZE / 2;
		if ((*param)->map[i][j] == 'N')
			(*param)->p_direction = N;
		else if ((*param)->map[i][j] == 'S')
			(*param)->p_direction = S;
		else if ((*param)->map[i][j] == 'W')
			(*param)->p_direction = W;
		else if ((*param)->map[i][j] == 'E')
			(*param)->p_direction = E;
		return (true);
	}
	return (false);
}

t_bool	check_player(t_mapinfo **param)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while ((*param)->map[i])
	{
		j = 0;
		while ((*param)->map[i][j])
		{
			if (init_player(param, i, j))
				count++;
			j++;
		}
		i++;
	}
	if (count == 1)
		return (true);
	return (false);
}