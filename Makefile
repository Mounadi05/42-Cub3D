src = 		parsing/parsing.c\
			parsing/parsing_helper1.c\
			parsing/parsing_helper2.c\
			parsing/parsing_helper3.c\
			parsing/parsing_helper4.c\
			parsing/parsing_helper5.c\
			parsing/parsing_helper6.c\
			raycasting/raycasting.c\
			raycasting/raycasting1.c\
			raycasting/raycasting2.c\
			raycasting/raycasting3.c\
			raycasting/raycasting4.c\

libft = 	libft/ft_atoi.c\
			libft/ft_get_next_line_utils.c\
			libft/ft_strncmp.c\
			libft/ft_get_next_line.c\
			libft/ft_split.c libft/ft_strrchr.c

lib = libft.a
name = cub3D
mlx = -lmlx -framework OpenGL -framework AppKit
CC = gcc -Wall -Wextra -Werror
obj = $(src:.c=.o)


all : $(name)

%.o: %.c
	$(CC) -c $< -o $@

$(name) : $(obj)
	$(CC) -O3 $(mlx) $(src) $(libft) cub3d.c  -o $(name)

clean:
	rm -rf $(obj)

fclean: clean
	rm -rf $(name)

re: fclean $(name)