src = 	ft_main.c\
			parsing/parsing.c\
			parsing/parsing_helper1.c\
			parsing/parsing_helper2.c\
			parsing/parsing_helper3.c\
			parsing/parsing_helper4.c\
			parsing/parsing_helper5.c\
			parsing/parsing_helper6.c

libft = 	libft/ft_atoi.c\
			libft/ft_get_next_line_utils.c\
			libft/ft_strncmp.c\
			libft/ft_get_next_line.c\
			libft/ft_split.c libft/ft_strrchr.c

lib = libft.a
name = cub3D
mlx = -lmlx -framework OpenGL -framework AppKit

all :
	gcc  -Wall -Wextra -Werror -O3 $(mlx) $(src) $(libft) cub3d.c   -o $(name)  