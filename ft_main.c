#include "include/cub3d.h"

void	my_mlx_pixel_put(t_mapinfo	*result, int x, int y, int color)
{
    result->data.addr[y * result->mlx.width + x] = color;
}
void draw_wall(t_mapinfo	*result)
{
    double h =result->mlx.height/2;
    for(double i = result->p_y - sin(result->view - result->point) * result->d_wall; i < h && i <  (int)(result->p_y + i - sin(result->view)) < result->mlx.height ;i+=0.1)
    {
        for(int a = 0 ; a < 360 ; a++)
            my_mlx_pixel_put(result,result->p_x + a + cos(result->view) * result->d_wall ,result->p_y + i - sin(result->view),0x00FF00);
    }
}
void raycasting(t_mapinfo	*result)
{
    double radius = 0;
    double i = 0.00;
    radius = 0;
    while(i <= 0.52)
    {
        radius = 0;
        while(1){
            if (result->map[(int)(result->p_y - sin(result->view - i) * radius)/40][(int)(result->p_x - cos(result->view - i) * radius)/40] != '1')
                my_mlx_pixel_put(result,result->p_x - cos(result->view - i) * radius,result->p_y - sin(result->view - i) * radius,0xf0fff0);
            else
            {
                result->d_wall = radius*40;
                result->point = i;
               // draw_wall(result);
                break;
            }
            radius++;
        }
        i+=0.02;
    }
    i = 0.00;
    while(i <= 0.52)
    {
        radius = 0;
        while(1){
            if (result->map[(int)(result->p_y - sin(result->view + i) * radius)/40][(int)(result->p_x - cos(result->view + i) * radius)/40] != '1')
                my_mlx_pixel_put(result,result->p_x - cos(result->view + i) * radius,result->p_y - sin(result->view + i) * radius,0xf0fff0);
            else
            {
                result->d_wall = radius*40;
                result->point = i;
              //  draw_wall(result);
                break;
            }
            radius++;
        }
        i+=0.02;
    }
}
void draw_player(t_mapinfo	*result){
    double radius = 0;
    double i;
    while(radius < 10)
    {
        i = 0;
        while(i < 50)
        {
            my_mlx_pixel_put(result,result->p_x + cos(i) * radius,result->p_y + sin(i) * radius,0xffffff);
            i+=0.5;
        }
        radius++;
    }
   raycasting(result);
}
void draw_Square(t_mapinfo	*result,int y, int x,int color)
{
    int i = 0;
    int j = 0;
    while(i < 40)
    {
        j = 0;
        while(j < 40)
        {
            my_mlx_pixel_put(result,x+j,y+i,color);
            j++;
        }
        i++;
    }
}
void draw_map(t_mapinfo	*result)
{
    int i = 0;
    int j = 0;
    while(result->map[i])
    {
        j = 0;
        while(result->map[i][j])
        {
            if( result->map[i][j] && result->map[i][j] == '1')
                draw_Square(result,i*40,j*40,0xFF0000);
            j++;
        }
        i++;
    }
}
int update(t_mapinfo	*result){
    mlx_destroy_image(result->mlx.ptr,result->data.img);
    result->data.img = mlx_new_image(result->mlx.win, result->mlx.width, result->mlx.height);
    result->data.addr = (int *)mlx_get_data_addr(result->data.img, &result->data.bits_per_pixel, &result->data.line_length,&result->data.endian);
    draw_map(result);
    draw_player(result);
    mlx_put_image_to_window(result->mlx.ptr, result->mlx.win, result->data.img, 0, 0);
    return 1;
}
void up(t_mapinfo	*result)
{
    if (result->map[(int)(result->p_y - 15 * sin(result->view))/40][(int)(result->p_x - 15 * cos(result->view))/40] != '1')
    {   
        result->p_x -= 15 * cos(result->view);
        result->p_y -= 15 * sin(result->view);
    }
}
void down(t_mapinfo	*result)
{
    if (result->map[(int)(result->p_y + 15 * sin(result->view))/40][(int)(result->p_x + 15 * cos(result->view))/40] != '1')
    {    
        result->p_x += 15 * cos(result->view);
        result->p_y += 15 * sin(result->view);
    }
}
void right(t_mapinfo	*result)
{
    result->view += 0.2;
}
void left(t_mapinfo	*result)
{
    result->view -= 0.2;
}
int move(int key ,t_mapinfo	*result)
{   
    if (key == KEY_UP)
        up(result);
    if (key == KEY_DOWN)
        down(result);
    if (key == KEY_RIGHT)
        right(result);
     if (key == KEY_LEFT)
        left(result);
    return 1;
}

void ft_main	(t_mapinfo	*result)
{
	result->mlx.ptr = mlx_init();
    result->mlx.height = result->len_y * 40;
    result->mlx.width = result->len_x * 40;
    result->mlx.win = mlx_new_window(result->mlx.ptr,result->mlx.width, result->mlx.height, "Cup3D");
    result->data.img = mlx_new_image(result->mlx.win, result->mlx.width, result->mlx.height);
    result->data.addr = (int *)mlx_get_data_addr(result->data.img, &result->data.bits_per_pixel, &result->data.line_length,&result->data.endian);
    draw_player(result);
	mlx_put_image_to_window(result->mlx.ptr, result->mlx.win, result->data.img, 0, 0);
	mlx_hook(result->mlx.win, 2, 0, move, result);
    mlx_loop_hook(result->mlx.ptr, update, result);
   	mlx_loop(result->mlx.ptr);
}