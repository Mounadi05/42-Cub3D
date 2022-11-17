/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:26:30 by ytaya             #+#    #+#             */
/*   Updated: 2022/10/29 20:19:18 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	ft_getnwords(char const *s, char c)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			n++;
			while (s[i + 1] && s[i + 1] != c)
				i++;
		}
		i++;
	}
	return (n);
}

static int	ft_getwordsize(const char *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static char	*ft_strucpy(char const *s, char c)
{
	int		i;
	char	*dest;

	i = 0;
	dest = (char *) malloc(sizeof(char) * (ft_getwordsize(s, c) + 1));
	if (!dest)
		return (0);
	while (s[i] && s[i] != c)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	*from;
	int		i;
	int		j;
	char	**table;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	table = (char **) malloc(sizeof(char *) * (ft_getnwords(s, c) + 1));
	if (!table)
		return (0);
	while (s[i])
	{
		if (s[i] != c)
		{
			from = (char *) &s[i];
			while (s[i + 1] && s[i + 1] != c)
				i++;
			table[j++] = ft_strucpy(from, c);
		}
		i++;
	}
	table[j] = NULL;
	return (table);
}
