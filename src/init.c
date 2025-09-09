#include "../include/cub3d.h"

void    put_pixel(int x, int y, int color, t_game *env)
{
    // int index;
    
    // if(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
    //     return ;
    // index = y * env->size_line + x * env->bpp / 8;
    // env->data[index] = color & 0xFF;
    // env->data[index + 1] = (color >> 8) & 0xFF;
    // env->data[index + 2] = (color >> 16) & 0xFF;
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
char    **get_map(void)
{
    char    **map;

    map = ft_malloc(sizeof(char *)  * 10);
    map[0] = "1111111111111";
    map[1] = "1000000000001";
    map[2] = "1000000000001";
    map[3] = "1000000000001";
    map[4] = "1000000000001";
    map[5] = "1000000000001";
    map[6] = "1000000000001";
    map[7] = "1000000000001";
    map[8] = "1111111111111";
    map[9] = NULL;
    return (map);
}

void	init_game(t_game *env)
{
	init_player(&env->player);
    env->map.grid = get_map();
    env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "Cube3D");
	env->img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
    env->address = mlx_get_data_addr(env->img, &env->bpp, &env->size_line, &env->endian);
}

void    init_player(t_player *player)
{
    player->x = WIDTH / 2;
    player->y = HEIGHT / 2;
    
    player->key_down = false;
    player->key_up = false;
    player->key_left = false;
    player->key_right = false;
    player->key_esc = false;
}

int key_press(int keycode, t_game *env)
{
    if (keycode == W)
        env->player.key_up = true;
    if (keycode == S)
        env->player.key_down = true;
    if (keycode == A)
        env->player.key_left = true;
    if (keycode == D)
        env->player.key_right = true;
    if (keycode == ESC)
		close_win(env);
    return (0);
}

int key_release(int keycode, t_game *env)
{
    if (keycode == W)
        env->player.key_up = false;
    if (keycode == S)
        env->player.key_down = false;
    if (keycode == A)
        env->player.key_left = false;
    if (keycode == D)
        env->player.key_right = false;
    return (0);
}

void    move_player(t_player *player)
{
    int speed;

    speed = 5;
    if (player->key_up)
        player->y -= speed;
    if (player->key_down)
        player->y += speed;
    if (player->key_left)
        player->x -= speed;
    if (player->key_right)
        player->x += speed;
}
void    clear_image(t_game * env)
{
    int y;
    int x;

    y = 0;
    x = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while(x < WIDTH)
        {
            put_pixel(x, y, 0, env);
            x++;
        }
        y++;
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

        }
    }

}

int draw_loop(t_game *env)
{
    t_player    *player;

    player = &env->player;
    move_player(player);
    clear_image(env);
    draw_square(player->x, player->y, 50, 0x00FF00, env);
    draw_map(env);
    mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
    return (0);

}
int	close_win(t_game *env)
{
    if (env->img)
        mlx_destroy_image(env->mlx, env->img);
    if (env->win)
        mlx_destroy_window(env->mlx, env->win);
    if (env->mlx)
    {
        mlx_destroy_display(env->mlx);
        free(env->mlx);
    }
    exit(0);
}

int main(void)
{
	t_game	env;

	init_game(&env);
    
    mlx_hook(env.win, 2, 1L<<0, key_press, &env);
    mlx_hook(env.win, 3, 1L<<1, key_release, &env);
    mlx_hook(env.win, 17, 0, close_win, &env);
    mlx_loop_hook(env.mlx, draw_loop, &env);
	mlx_loop(env.mlx);

	return (0);
}