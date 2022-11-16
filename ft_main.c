#include "include/cub3d.h"

void	my_mlx_pixel_put(t_mapinfo	*result, int x, int y, int color)
{
    if (x >= 0 && y >= 0 &&  x < result->mlx.width && y < result->mlx.height)
        result->data.addr[y * result->mlx.width + x] = color;
}
int draw_xmp(t_mapinfo *result,int x ,int y)
{ 
    
    return result->add_wall[(y%64) * 64 + (x%64)];
}
 
void draw_wall(t_mapinfo *result)
{
    double dis;
    int index = 0;
    int wall = (result->mlx.width/result->len_ry) + 1;
      while (index < result->len_ry){
        dis = (64 / floorf(result->d_wall[index])) * (result->mlx.height/tan(0.53));
        dis = floorf(dis);
        int max = result->mlx.height/2 + (int)dis/2 + 1;
        for(int a = result->mlx.height/2 - dis/2 + 1; a < result->mlx.height &&  a <= max; a++)
        {
            int y = (double)(a - (result->mlx.height/2 - (dis/2)+1)) * (64.0 / dis);
            for(int b = 0; b <= wall && b + (index * wall) < result->mlx.width ; b++)
                my_mlx_pixel_put(result,b + (index * wall) ,a ,draw_xmp(result, result->w_x[index], y));
        }
        index++;
    }
}
void raycasting(t_mapinfo	*result)
{
    double radius = 0;
    double i = result->view - 0.5236;
    radius = 0;
    int in = 0;
    int a = 0;
    result->d_wall = malloc(8000);
    result->w_x = malloc(8000);
    result->point = malloc(8000);
    while(i < result->view + 0.5236)
    {   
        radius = 0;
        while((int)(result->p_x + cos(i) * radius) < result->mlx.width && (int)(result->p_y + sin(i) * radius) < result->mlx.height ){
            if (result->map[(int)(result->p_y + sin(i) * radius)/64][(int)(result->p_x + cos(i) * radius)/64] != '1')
            {
             // my_mlx_pixel_put(result,result->p_x + cos(i) * radius,result->p_y + sin(i) * radius,0xf0fff0);
                 ;
            }
            else if (result->map[(int)(result->p_y + sin(i) * (radius - 1))/64][(int)(result->p_x + cos(i) * (radius))/64] != '1')
            {   
                result->point[in] = 1.0;
                result->d_wall[in] = radius * cos(result->view - i);
                result->w_x[in++] = (int)(result->p_x + cos(i) * (radius));
                break;
            }
            else if (result->map[(int)(result->p_y + sin(i) * (radius))/64][(int)(result->p_x + cos(i) * (radius - 1))/64] != '1')
            {
                result->d_wall[in] = radius* cos(result->view - i);
                result->point[in] = 0.0;
                result->w_x[in++] = (int)(result->p_y + sin(i) * (radius));
                break;      
            }
            radius +=1;
        }
        i+=0.002;
        a++;
    }
    result->len_ry = a;
    draw_wall(result);
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
int update(t_mapinfo	*result){
   
        usleep(100);
        mlx_destroy_image(result->mlx.ptr,result->data.img);
        result->data.img = mlx_new_image(result->mlx.win, result->mlx.width, result->mlx.height);
        result->data.addr = (int *)mlx_get_data_addr(result->data.img, &result->data.bits_per_pixel, &result->data.line_length,&result->data.endian);
        draw_nowall(result);
        draw_flor(result);
        raycasting(result);
        mlx_put_image_to_window(result->mlx.ptr, result->mlx.win, result->data.img, 0, 0);

    return 1;
}
void up(t_mapinfo	*result)
{        
    if (result->map[(int)(result->p_y + 20 * sin(result->view))/64][(int)(result->p_x + 20 * cos(result->view))/64] != '1')
    {   
        result->active = 1;  
        result->p_x += 15 * cos(result->view);
        result->p_y += 15 * sin(result->view);
    }
}
void down(t_mapinfo	*result)
{
    if (result->map[(int)((result->p_y - 20 * sin(result->view))/64)][(int)(result->p_x - 20 * cos(result->view))/64] != '1')
    {     
        result->active = 1;       
        result->p_x -= 15 * cos(result->view);
        result->p_y -= 15 * sin(result->view);
    }
}
void right(t_mapinfo	*result)
{
    result->active = 1;  
    result->view += 0.2;
    result->active= 1;

}
void left(t_mapinfo	*result)
{
      result->active = 1;  
    result->view -= 0.2;
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

void ft_main	(t_mapinfo	*result)
{
	result->mlx.ptr = mlx_init();
    result->mlx.height = 1000;
    result->mlx.width =  2000;
    result->mlx.win = mlx_new_window(result->mlx.ptr,result->mlx.width, result->mlx.height, "Cup3D");
    result->data.img = mlx_new_image(result->mlx.win, result->mlx.width, result->mlx.height);
    result->data.addr = (int *)mlx_get_data_addr(result->data.img, &result->data.bits_per_pixel, &result->data.line_length,&result->data.endian);
    int h = 64;
    int w = 64;
    int bits_per_pixel;
    int line_length;
    int endian ;
    result->img_wall = mlx_xpm_file_to_image(result->mlx.ptr,result->no, &h,&w);
    result->add_wall = (int *)mlx_get_data_addr(result->img_wall, &bits_per_pixel, &line_length,&endian);
   // draw_player(result);
//    for(int a = 0 ; a < 500;a++)
//         for(int b =0; b < 500;b++)
//             my_mlx_pixel_put(result,b , a ,draw_xmp(result,(b*64)/500,(a * 64)/500));
	mlx_put_image_to_window(result->mlx.ptr, result->mlx.win, result->data.img, 0, 0);
	mlx_hook(result->mlx.win, 2, 0, move, result);
    mlx_loop_hook(result->mlx.ptr, update, result);
   	mlx_loop(result->mlx.ptr);
}