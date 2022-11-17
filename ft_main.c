#include "include/cub3d.h"

void	my_mlx_pixel_put(t_mapinfo	*result, int x , int y, int color)
{
    if (x >= 0 && y >= 0 &&  x < result->mlx.width && y < result->mlx.height)
        result->data.addr[y * result->mlx.width + x] = color;
}

int draw_xmp(t_mapinfo *result,int x ,int y,double v_x,double v_y)
{   
    if (x%64 < 0)
        x = 0;
    if (y %64 < 0)
        y = 0;
    if (v_x == 0)
        return result->add_wall_no[(y%64) * 64 + (x%64)];
    if(v_x == 63)
        return result->add_wall_so[(y%64) * 64 + (x%64)];
    if(v_y == 63)
        return result->add_wall_we[(y%64) * 64 + (x%64)];
    return result->add_wall_ea[(y%64) * 64 + (x%64)];

}
 
void draw_wall(t_mapinfo *result)
{
    double dis;
    int index = 0;
    int y;
    int wall = (result->mlx.width/result->len_ry) + 1;
    while (index < result->len_ry)
    {
        dis = (64 / floorf(result->d_wall[index])) * (result->mlx.height/tan(0.53));
        dis = floorf(dis);
        int max = result->mlx.height/2 + (int)dis/2 + 1;
        for(int a = result->mlx.height/2 - dis/2 + 1; a < result->mlx.height &&  a <= max; a++)
        {
            y = (a - (result->mlx.height/2 - (dis/2)+1)) * (64.0 / dis);
            for(int b = 0; b < wall && b + (index * wall) < result->mlx.width ; b++)
            my_mlx_pixel_put(result,b + (index * wall) ,a ,draw_xmp(result, result->w_x[index],y,result->point_x[index],result->point_y[index]));
        }
        index++;
    }
}

void raycasting(t_mapinfo	*result)
{
    double radius = 0;
    double i = result->p_direction - 0.5236;
    radius = 0;
    int in = 0;
    int a = 0;
    while(i < result->p_direction+ 0.5236)
    {   
        radius = 0;
        while(1){
            if (result->map[(int)(result->p_y + sin(i) * radius)/64][(int)(result->p_x + cos(i) * radius)/64] && result->map[(int)(result->p_y + sin(i) * radius)/64][(int)(result->p_x + cos(i) * radius)/64] != '1')
                 ;
            else if (result->map[(int)(result->p_y + sin(i) * (radius - 1))/64][(int)(result->p_x + cos(i) * (radius))/64] && result->map[(int)(result->p_y + sin(i) * (radius - 1))/64][(int)(result->p_x + cos(i) * (radius))/64] == '1')
            {   
                result->d_wall[in] = radius * cos(result->p_direction - i);
                result->w_x[in] = (int)(result->p_y + sin(i) * (radius));
                result->point_y[in] = (int)(result->p_y + sin(i) * radius)%64;
                result->point_x[in++] = (int)(result->p_x + cos(i) * radius)%64;
                break;
            }
            else if (result->map[(int)(result->p_y + sin(i) * (radius))/64][(int)(result->p_x + cos(i) * (radius - 1))/64] && result->map[(int)(result->p_y + sin(i) * (radius))/64][(int)(result->p_x + cos(i) * (radius - 1))/64] == '1')
            {
                result->d_wall[in] = radius* cos(result->p_direction - i);
                result->w_x[in] = (int)(result->p_x + cos(i) * (radius));
                result->point_y[in] = (int)(result->p_y + sin(i) * radius)%64;
                result->point_x[in++] = (int)(result->p_x + cos(i) * radius)%64;
                break;
            }
            radius +=1;
        }
        i+=0.0015;
        a++;
    }
    result->len_ry = a;
    draw_wall(result);
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
            my_mlx_pixel_put(result,j,i,0xFFFFFF);
            j++;
        }
        i++;
    }
}

int update(t_mapinfo	*result)
{
    if (result->active)
    {
        result->active = 0;
        mlx_destroy_image(result->mlx.ptr,result->data.img);
        mlx_clear_window(result->mlx.ptr,result->mlx.win);
        result->data.img = mlx_new_image(result->mlx.ptr, result->mlx.width, result->mlx.height);
        result->data.addr = (int *)mlx_get_data_addr(result->data.img, &result->data.bits_per_pixel, &result->data.line_length,&result->data.endian);
        draw_nowall(result);
        draw_flor(result);
        raycasting(result);
        mlx_put_image_to_window(result->mlx.ptr, result->mlx.win, result->data.img, 0, 0);
    }
    return 1;
}

void up(t_mapinfo	*result)
{        
    if (result->map[(int)(result->p_y + 25 * sin(result->p_direction))/64][(int)(result->p_x + 25 * cos(result->p_direction))/64] != '1')
    {   
        result->active = 1;       
        result->p_x += 15 * cos(result->p_direction);
        result->p_y += 15 * sin(result->p_direction);
    }
}

void down(t_mapinfo	*result)
{
    if (result->map[(int)((result->p_y - 25 * sin(result->p_direction))/64)][(int)(result->p_x - 25 * cos(result->p_direction))/64] != '1')
    {     
        result->active = 1;       
        result->p_x -= 15 * cos(result->p_direction);
        result->p_y -= 15 * sin(result->p_direction);
    }
}

void right(t_mapinfo	*result)
{
    result->p_direction += 0.15;
    result->active= 1;
}

void left(t_mapinfo	*result)
{
    result->p_direction -= 0.15;
    result->active= 1;
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

void init_img(t_mapinfo *result)
{
    int h;
    int w;
    int bits_per_pixel;
    int line_length;
    int endian;
    
    h = 64;
    w = 64;
    result->img_wall_no = mlx_xpm_file_to_image(result->mlx.ptr,result->no, &h,&w);
    result->add_wall_no = (int *)mlx_get_data_addr(result->img_wall_no, &bits_per_pixel, &line_length,&endian);
    result->img_wall_so = mlx_xpm_file_to_image(result->mlx.ptr,result->so, &h,&w);
    result->add_wall_so = (int *)mlx_get_data_addr(result->img_wall_so, &bits_per_pixel, &line_length,&endian);
    result->img_wall_we = mlx_xpm_file_to_image(result->mlx.ptr,result->we, &h,&w);
    result->add_wall_we = (int *)mlx_get_data_addr(result->img_wall_we, &bits_per_pixel, &line_length,&endian);
    result->img_wall_ea = mlx_xpm_file_to_image(result->mlx.ptr,result->ea, &h,&w);
    result->add_wall_ea = (int *)mlx_get_data_addr(result->img_wall_ea, &bits_per_pixel, &line_length,&endian);
}

void ft_main	(t_mapinfo	*result)
{
	result->mlx.ptr = mlx_init();
    result->mlx.height = 1000;
    result->mlx.width =  2000;
    result->mlx.win = mlx_new_window(result->mlx.ptr,result->mlx.width, result->mlx.height, "Cub3D");
    result->data.img = mlx_new_image(result->mlx.ptr, result->mlx.width, result->mlx.height);
    result->data.addr = (int *)mlx_get_data_addr(result->data.img, &result->data.bits_per_pixel, &result->data.line_length,&result->data.endian);
    init_img(result);
	mlx_hook(result->mlx.win, 2, 0, move, result);
    mlx_loop_hook(result->mlx.ptr, update, result);
    mlx_loop(result->mlx.ptr);
}