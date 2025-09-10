#include "../include/cub3d.h"


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
    player->angle = PI / 2;
    
    player->key_down = false;
    player->key_up = false;
    player->key_left = false;
    player->key_right = false;
    player->key_esc = false;
    player->left_rotate = false;
    player->right_rotate = false;
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