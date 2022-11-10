#include "include/cub3d.h"

void	my_mlx_pixel_put(t_mapinfo	*result, int x, int y, int color)
{
    if (x >= 0 && y >= 0 &&  x < result->mlx.width && y < result->mlx.height)
        result->data.addr[y * result->mlx.width + x] = color;
}
void draw_wall(t_mapinfo *result)
{
    double dis;
    int index = 0;
    int wall = result->mlx.width/result->len_ry;
    while (index < result->len_ry){
        dis = (44 / result->d_wall[index]) * (result->mlx.height/tan(0.52));
        for(int a = result->mlx.height/2 - dis/2; a < result->mlx.height &&  a < result->mlx.height/2 + (int)dis; a++)
            for(int b = 0; b < wall && b + (index * wall) < result->mlx.width ; b++)
            my_mlx_pixel_put(result,b + (index * wall),a ,0xFFF000);
        index++;
    }
}
void raycasting(t_mapinfo	*result)
{
    double radius = 0;
    double i = result->view - 0.52;
    radius = 0;
    int in = 0;
    int a = 0;
    result->d_wall = malloc(8000);
    while(i <= result->view + 0.52)
    {   
        radius = 0;
        while(1 && (int)(result->p_x + cos(i) * radius) < result->mlx.width &&(int)(result->p_y + sin(i) * radius)< result->mlx.height ){
            if ( result->map[(int)(result->p_y + sin(i) * radius)/44][(int)(result->p_x + cos(i) * radius)/44] && result->map[(int)(result->p_y + sin(i) * radius)/44][(int)(result->p_x + cos(i) * radius)/44] != '1')
            {
             // my_mlx_pixel_put(result,result->p_x + cos(i) * radius,result->p_y + sin(i) * radius,0xf0fff0);
                 ;
            }
            else
            {
                result->d_wall[in++] = radius;
                break;
            }
            radius +=0.5;
        }
        i+=0.004;
        a++;
    }
    result->len_ry = a-1;
   draw_wall(result);
}
 
void draw_player(t_mapinfo	*result,int l){
    double radius = 0;
    double i;
    while(radius < 4)
    {
        i = 0;
        while(i < 40)
        {
            my_mlx_pixel_put(result,(result->mp_x * l) + cos(i) * radius,(result->mp_y * l) + sin(i) * radius,0x000000);
            i+=0.5;
        }
        radius++;
    }
}

void draw_Square(t_mapinfo	*result,int y, int x,int color,int l)
{
    int i = 0;
    int j = 0;
    while(i < l)
    {
        j = 0;
        while(j < l)
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
    int l = 400/result->len_x;
    while(result->map[i])
    {
        j = 0;
        while(result->map[i][j])
        {
            if( result->map[i][j] && result->map[i][j] == '1')
                draw_Square(result,i*l,j*l,0xFF0000,l);
            j++;
        }
        i++;
    }
    draw_player(result,l);
}

void draw_nowall(t_mapinfo *result)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(i < result->mlx.height/2)
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
void draw_flor(t_mapinfo *result)
{
    int i;
    int j;

    i = result->mlx.height/2;
    j = 0;
    while(i < result->mlx.height)
    {
        j = 0;
        while(j < result->mlx.width)
        {
            my_mlx_pixel_put(result,j,i,0x7a5104);
            j++;
        }
        i++;
    }
}
int update(t_mapinfo	*result){
    mlx_destroy_image(result->mlx.ptr,result->data.img);
    result->data.img = mlx_new_image(result->mlx.win, result->mlx.width, result->mlx.height);
    result->data.addr = (int *)mlx_get_data_addr(result->data.img, &result->data.bits_per_pixel, &result->data.line_length,&result->data.endian);
    draw_nowall(result);
    draw_flor(result);
    raycasting(result);
    draw_map(result);
    mlx_put_image_to_window(result->mlx.ptr, result->mlx.win, result->data.img, 0, 0);
    return 1;
}
void up(t_mapinfo	*result)
{
    if (result->map[(int)(result->p_y + 15 * sin(result->view))/44][(int)(result->p_x + 15 * cos(result->view))/44] != '1')
    {   
        result->p_x += 15 * cos(result->view);
        result->p_y += 15 * sin(result->view);
        result->mp_x += 0.2 * cos(result->view);
        result->mp_y += 0.2 * sin(result->view);
    }
}
void down(t_mapinfo	*result)
{
    if (result->map[(int)(result->p_y - 15 * sin(result->view))/44][(int)(result->p_x - 15 * cos(result->view))/44] != '1')
     {    
        result->p_x -= 15 * cos(result->view);
        result->p_y -= 15 * sin(result->view);
        result->mp_x -= 0.2 * cos(result->view);
        result->mp_y -= 0.2 * sin(result->view);
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
    result->mlx.width =  result->len_x*44 + 44;
    result->mlx.win = mlx_new_window(result->mlx.ptr,result->mlx.width, result->mlx.height, "Cup3D");
    result->data.img = mlx_new_image(result->mlx.win, result->mlx.width, result->mlx.height);
    result->data.addr = (int *)mlx_get_data_addr(result->data.img, &result->data.bits_per_pixel, &result->data.line_length,&result->data.endian);
   // draw_player(result);
	mlx_put_image_to_window(result->mlx.ptr, result->mlx.win, result->data.img, 0, 0);
	mlx_hook(result->mlx.win, 2, 0, move, result);
    mlx_loop_hook(result->mlx.ptr, update, result);
   	mlx_loop(result->mlx.ptr);
}