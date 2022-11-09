#include "include/cub3d.h"

void	my_mlx_pixel_put(t_mapinfo	*result, int x, int y, int color)
{
    result->data.addr[y * result->mlx.width + x] = color;
}
void draw_wall(t_mapinfo *result)
{
    double dis;
    int index = 0;
    // int wall = result->mlx.width/result->len_ry;
    while (index < result->len_ry ){
        if (result->d_wall[index] <= 0)
            dis = 44 * 450;
        else
            dis = (44 / result->d_wall[index]) * 450;
        for(int a = 0; a < (int)dis; a++)
            for(int b = 0; b < 44 && b + (index * 44) < result->mlx.width && a < result->mlx.height ; b++)
            my_mlx_pixel_put(result,b + (index * 44),a ,0xFFF000);
        index++;
    }

}
void raycasting(t_mapinfo	*result)
{
    double radius = 0;
    double i = result->view - 0.52;
    printf("%f\n",i);
    radius = 0;
    int in = 0;
    int a = 0;
    result->d_wall = malloc(8000);
    while(i <= result->view + 0.52)
    {   
        radius = 0;
        while(1 && (int)(result->p_x + cos(i) * radius) + 100 < result->mlx.width &&(int) (result->p_y + sin(i) * radius) + 100 < result->mlx.height ){
            if (result->map[(int)(result->p_y + sin(i) * radius)/44][(int)(result->p_x + cos(i) * radius)/44] != '1')
            {
              //my_mlx_pixel_put(result,result->p_x + cos(i) * radius,result->p_y + sin(i) * radius,0xf0fff0);
                ;
            }
            else
            {
                result->d_wall[in++] = radius;
                result->point = i;
                break;
            }
            radius++;
        }
        i+=0.01;
        a++;
    }
    result->len_ry = a;
    draw_wall(result);
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
    while(i < 44)
    {
        j = 0;
        while(j < 44)
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
                draw_Square(result,i*44,j*44,0xFF0000);
            j++;
        }
        i++;
    }
}
void draw_nowall(t_mapinfo *result)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(i < result->mlx.height)
    {
        j = 0;
        while(j < result->mlx.width)
        {
            my_mlx_pixel_put(result,j,i,0x76cce8);
            j++;
        }
        i++;
    }
}
int update(t_mapinfo	*result){
    mlx_destroy_image(result->mlx.ptr,result->data.img);
    result->data.img = mlx_new_image(result->mlx.win, result->mlx.width, result->mlx.height);
    result->data.addr = (int *)mlx_get_data_addr(result->data.img, &result->data.bits_per_pixel, &result->data.line_length,&result->data.endian);
 //draw_map(result);
 draw_player(result);
  draw_nowall(result);
   raycasting(result);
    mlx_put_image_to_window(result->mlx.ptr, result->mlx.win, result->data.img, 0, 0);

    return 1;
}
void up(t_mapinfo	*result)
{
     if (result->map[(int)(result->p_y - 15 * sin(result->view))/40][(int)(result->p_x - 15 * cos(result->view))/40] != '1')
     {   
        result->p_x += 15 * cos(result->view);
        result->p_y += 15 * sin(result->view);
     }
}
void down(t_mapinfo	*result)
{
    if (result->map[(int)(result->p_y + 15 * sin(result->view))/40][(int)(result->p_x + 15 * cos(result->view))/40] != '1')
     {    
        result->p_x -= 15 * cos(result->view);
        result->p_y -= 15 * sin(result->view);
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
    result->mlx.height = result->len_y*44;
    result->mlx.width =  result->len_x*44;
    result->mlx.win = mlx_new_window(result->mlx.ptr,result->mlx.width, result->mlx.height, "Cup3D");
    result->data.img = mlx_new_image(result->mlx.win, result->mlx.width, result->mlx.height);
    result->data.addr = (int *)mlx_get_data_addr(result->data.img, &result->data.bits_per_pixel, &result->data.line_length,&result->data.endian);
    draw_player(result);
	mlx_put_image_to_window(result->mlx.ptr, result->mlx.win, result->data.img, 0, 0);
	mlx_hook(result->mlx.win, 2, 0, move, result);
    mlx_loop_hook(result->mlx.ptr, update, result);
   	mlx_loop(result->mlx.ptr);
}