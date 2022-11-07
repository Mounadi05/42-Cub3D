/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounadi05 <mounadi2015@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:26:12 by ytaya             #+#    #+#             */
/*   Updated: 2022/11/07 05:01:46 by mounadi05        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>
# include <mlx.h>
# include <math.h>

# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126


typedef struct	s_data {
	void	*img;
	int	    *addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}t_data;

typedef struct s_mlx
{
    void *ptr;
    void *win;
    int width; 
    int height;
}t_mlx;

typedef struct color
{
	int	r;
	int	g;
	int	b;
}t_color;

typedef enum direction
{
	E = 0,
	S = 90,
	N = 270,
	W = 180
}	t_direction;

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef enum t_token
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	BADTOKEN
}	t_token;

// postion palayer x,y / x * ts + ts / 2; + deriction 0 | P | 2P | 3P
//  0 = ea | pi = So | 2pi = We | 3p = No

# define PI 3.14159265358979323846
# define TAILSIZE 64

typedef struct mapInfo
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	t_color		*f;
	t_color		*c;
	char		**map;
	double		p_x;
	double		p_y;
	double		view;
	t_direction	p_direction;
	t_data		data;
	t_mlx		mlx;
	int len_x;
	int len_y;
	double d_wall;
	double point ; 
}	t_mapinfo;

//parsing

void		int_mapinfo(t_mapinfo *param);
t_bool		valide_extention(char *filename, char *extention);
t_token		valide_token(char *token);
t_bool		valide_texter(char *path);
t_bool		is_6info(t_mapinfo *param);
t_color		*is_valide_color(char *param);
t_mapinfo	*map_parse(char *filename);
t_bool		is_empty(char *line);
char		*ft_toupper(char *str);
int			check_map(char **map);
int			valid(char **map, int j, int i, int maphight);
t_bool		read6info(t_mapinfo **param, int fd);
void		readmap(t_mapinfo *param, int fd);
int			getkeyvalue(t_mapinfo **param, char *line);
t_bool		is_number(char *param);
t_bool		valide_rgb(int n);
int			is_space(char space);
char		*strtrim(char *str);
void		handel_no(char *value, t_mapinfo **param);
void		handel_so(char *value, t_mapinfo **param);
void		handel_we(char *value, t_mapinfo **param);
void		handel_ea(char *value, t_mapinfo **param);
void		handel_f(char *value, t_mapinfo **param);
void		handel_c(char *value, t_mapinfo **param);
int			bad_token(char *value, char *key);
t_bool		check_player(t_mapinfo **param);

//libft

char		*ft_strrchr(const char *s, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_atoi(const char *nptr);
char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s1);
char		*ft_strchr(const char *s, int c);
char		*ft_strjoin(char *s1, char *s2);
void		ft_free(char **str);
char		*ft_delete_line(char *stock);
char		*ft_read_line(char *stock, int fd);
int			ft_strlen_newline(char *str);
char		*get_next_line(int fd);

void		ft_main(t_mapinfo	*result);

#endif