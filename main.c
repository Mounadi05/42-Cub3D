#include <unistd.h>
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define W 4.71239
#define N 1.5708
#define E 0
#define S 3.14159
typedef struct s_player
{
    double x;
    double y;
    double view;
    double camera;
}t_player;

typedef struct	s_data {
	void	*img;
	int	    *addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    int     len;
}t_data;

typedef struct s_mlx
{
    void *ptr;
    void *win;
    int width; 
    int height;
    t_data data;
    t_player player;
}t_mlx;
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
    mlx->data.addr[y * mlx->width + x] = color;
}
void draw_player(t_mlx *mlx){
    double radius = 0;
    double i;
    double j;
    while(radius < 15)
    {
        i = 0;
        while(i < 360)
        {
            my_mlx_pixel_put(mlx,mlx->player.x + cos(i) * radius,mlx->player.y + sin(i) * radius,0xffffff);
            i+=0.5;
        }
        radius++;
    }
    radius = 0;
    while(radius < 200){
            my_mlx_pixel_put(mlx,mlx->player.x - cos(mlx->player.view) * radius,mlx->player.y - sin(mlx->player.view) * radius,0xff0ff0);
        radius++;
    }
}
void init_player(t_player *t)
{
    t->x = 510;
    t->y = 510;
    t->view = N;
}

int update(t_mlx *mlx){
    mlx_destroy_image(mlx->ptr,mlx->data.img);
    mlx->data.img = mlx_new_image(mlx->win, mlx->width, mlx->height);
    mlx->data.addr = (int *)mlx_get_data_addr(mlx->data.img, &mlx->data.bits_per_pixel, &mlx->data.line_length,&mlx->data.endian);
    draw_player(mlx);
    mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->data.img, 0, 0);
    return 1;
}
void up(t_mlx *mlx)
{
    int i = mlx->player.x;
    int j = mlx->player.y;
    mlx->player.x += 15 * cos(mlx->player.view);
    mlx->player.y += 15 * sin(mlx->player.view);
}
void down(t_mlx *mlx)
{
    int i = mlx->player.x;
    int j = mlx->player.y;
    mlx->player.x -= 15 * cos(mlx->player.view);
    mlx->player.y -= 15 * sin(mlx->player.view);
}
void right(t_mlx *mlx)
{
    int i = mlx->player.x;
    int j = mlx->player.y;
    mlx->player.view += 0.2;
}
void left(t_mlx *mlx)
{
    int i = mlx->player.x;
    int j = mlx->player.y;
    mlx->player.view -= 0.2;
}
int move(int key ,t_mlx *mlx)
{   
    if (key == 125)
        up(mlx);
    if (key == 126)
        down(mlx);
    if (key == 124)
        right(mlx);
     if (key == 123)
        left(mlx);
    return 1;
}

int	main(void)
{
    t_player p;
    t_mlx mlx;
    mlx.data.len = 10;
	mlx.ptr = mlx_init();
    mlx.win = mlx_new_window(mlx.ptr, 1800, 1200, "Cup3D");
    mlx.height = 1200;
    mlx.width = 1800;
    mlx.data.img = mlx_new_image(mlx.win, mlx.width, mlx.height);
    mlx.data.addr = (int *)mlx_get_data_addr(mlx.data.img, &mlx.data.bits_per_pixel, &mlx.data.line_length,&mlx.data.endian);
    int i = 0;
    i = 500;
    int j = 500;
    init_player(&mlx.player);
    draw_player(&mlx);
    mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.data.img, 0, 0);
	mlx_hook(mlx.win, 2, 0, move, &mlx);
    mlx_loop_hook(mlx.ptr, update, &mlx);
    mlx_loop(mlx.ptr);
}