/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:07:46 by ytaya             #+#    #+#             */
/*   Updated: 2022/10/30 05:34:55 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*get_key(char *line, int *f)
{
	int		i;
	int		n;
	char	*key;
	int		j;

	i = 0;
	j = 0;
	while (line[i] && !is_space(line[i]))
		i++;
	n = i;
	while (line[i] && is_space(line[i]))
		i++;
	*f = i;
	key = malloc(sizeof(char) * (i - n + 1));
	while (line[n] && is_space(line[n]))
		key[j++] = line[n++];
	key[j] = '\0';
	return (key);
}

int	getkeyvalue(t_mapinfo **param, char *line)
{
	char	*key;
	char	*value;
	int		i;

	key = get_key(line, &i);
	value = strtrim(line + i);
	if (valide_token(key) == NO)
		handel_no(value, param);
	else if (valide_token(key) == SO)
		handel_so(value, param);
	else if (valide_token(key) == WE)
		handel_we(value, param);
	else if (valide_token(key) == EA)
		handel_ea(value, param);
	else if (valide_token(key) == F)
		handel_f(value, param);
	else if (valide_token(key) == C)
		handel_c(value, param);
	else if (valide_token(key) == BADTOKEN)
		return (bad_token(value, key));
	else
		free(value);
	free(key);
	return (1);
}

void	handel_no(char *value, t_mapinfo **param)
{
	if (valide_texter(value) && !(*param)->no)
	{
		(*param)->no = value;
	}
	else
		printf("Error in NO\n");
}

void	handel_so(char *value, t_mapinfo **param)
{
	if (valide_texter(value) && !(*param)->so)
	{
		(*param)->so = value;
	}
	else
		printf("Error in SO\n");
}

void	handel_we(char *value, t_mapinfo **param)
{
	if (valide_texter(value) && !(*param)->we)
	{
		(*param)->we = value;
	}
	else
		printf("Error in WE\n");
}
