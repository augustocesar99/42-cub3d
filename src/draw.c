#include "../include/cub3d.h"

void    put_pixel(int x, int y, int color, t_game *env)
{

    char	*pxl;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pxl = env->address +(y * env->size_line
				+ x * (env->bpp / 8));
		*(unsigned int *)pxl = color;
	}
}

void    draw_square(int x, int y, int size, int color, t_game * env)
{
    int i;

    i = 0;
    while (i < size)
    {
        put_pixel(x + i, y, color, env);
        i++;
    }
    i = 0;
    while (i < size)
    {
        put_pixel(x, y + i, color, env);
        i++;
    }
    i = 0;
    while (i < size)
    {
        put_pixel(x + size, y + i, color, env);
        i++;
    }
    i = 0;
    while (i < size)
    {
        put_pixel(x + i, y + size, color, env);
        i++;
    }
}

void    move_player(t_player *player)
{
    int speed;
    double angle_speed;
    double  cos_angle;
    double  sin_angle;


    cos_angle = cos(player->angle);
    sin_angle = sin(player->angle);
    angle_speed = 0.1;
    speed = 3;
    if (player->left_rotate)
        player->angle -= angle_speed;
    if (player->right_rotate)
        player->angle += angle_speed;
    if (player->angle > 2 * PI)
        player->angle = 0;
    if (player->angle < 0)
        player->angle = 2 * PI;
    
    
    if (player->key_up)
    {
        player->x += cos_angle * speed;
        player->y += sin_angle * speed;
    }
    if (player->key_down)
    {
        player->x -= cos_angle * speed;
        player->y += sin_angle * speed;
    }
    if (player->key_left)
    {
        player->x += cos_angle * speed;
        player->y -= sin_angle * speed;
    }
    if (player->key_right)
    {
        player->x += cos_angle * speed;
        player->y += sin_angle * speed;
    }
}

void    draw_map(t_game * env)
{
    char    **map;
    int     color;
    int     y;
    int     x;

    y = 0;
    x = 0;
    map = env->map.grid;
    color = 0x0000FF;
    while (map[y])
    {
        x = 0;
        while(map[y][x])
        {
            if (map[y][x] == '1')
                draw_square(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, color, env);
            x++;
        }
        y++;
    }

}

int draw_loop(t_game *env)
{
    float       ray_x;
    float       ray_y;


    ray_x = env->player.x;
    ray_y = env->player.y;
    


    move_player(&env->player);
    clear_image(env);
    draw_square(env->player.x, env->player.y, 50, 0x00FF00, env);
    draw_map(env);



    mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
    return (0);

}

char    **get_map(void)
{
    char    **map;

    map = ft_malloc(sizeof(char *)  * 10);
    map[0] = "1111111111111";
    map[1] = "1010000000001";
    map[2] = "1010000000001";
    map[3] = "1000000000001";
    map[4] = "1000000000001";
    map[5] = "1000000000001";
    map[6] = "1000000000001";
    map[7] = "1000000000001";
    map[8] = "1111111111111";
    map[9] = NULL;
    return (map);
}