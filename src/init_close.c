#include "../include/cub3d.h"

static void	spawn(t_game *env)
{
	if (env->spawn_side == 'N')
		env->player.angle = 3 * PI / 2;
	else if (env->spawn_side == 'S')
		env->player.angle = PI / 2;
	else if (env->spawn_side == 'E')
		env->player.angle = 0;
	else if (env->spawn_side == 'W')
		env->player.angle = PI;
	else
		ft_printf("spawn error\n");
}

void	init_game(t_game *env)
{
	int	i;

	init_player(&env->player);
	//
	//take out after parser
	env->floor.value = 0x00303030;
	env->ceiling.value = 0x0080B4FF;
	env->map.grid = get_map();
	env->no_tex.path = "./textures/north.xpm";
	env->so_tex.path = "./textures/south.xpm";
	env->we_tex.path = "./textures/west.xpm";
	env->ea_tex.path = "./textures/east.xpm";
	env->spawn_side = 'W';
	//take out after parse
	spawn(env);
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "Cube3D");
	env->img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	env->address = mlx_get_data_addr(env->img,
			&env->bpp, &env->size_line, &env->endian);
	i = 0;
	while (i < 4)
	{
		set_tex_zero(&env->tex[i]);
		i++;
	}
	if (load_all_textures(env))
		ft_printf("texture error");
}

void	init_player(t_player *player)
{
	//take out after parser
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	//take out after parser
	player->key_down = false;
	player->key_up = false;
	player->key_left = false;
	player->key_right = false;
	player->key_esc = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

void	clear_image(t_game *env)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, env);
			x++;
		}
		y++;
	}
}

int	close_win(t_game *env)
{
	destroy_all_textures(env);
	if (env->img)
		mlx_destroy_image(env->mlx, env->img);
	if (env->win)
		mlx_destroy_window(env->mlx, env->win);
	if (env->mlx)
	{
		mlx_destroy_display(env->mlx);
		free(env->mlx);
	}
	free (env->map.grid);
	exit(0);
}
