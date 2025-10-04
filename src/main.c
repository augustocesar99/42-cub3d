#include "cub3d.h"

static void	init_parse_data(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game)); 
	game->parse.fd = -1;
}

// int close_win(t_game *env)
// {
// 	if (env->mlx)
// 	{
// 		if (env->img)
// 			mlx_destroy_image(env->mlx, env->img);

// 		if (env->no_tex.img)
// 			mlx_destroy_image(env->mlx, env->no_tex.img);
// 		if (env->so_tex.img)
// 			mlx_destroy_image(env->mlx, env->so_tex.img);
// 		if (env->we_tex.img)
// 			mlx_destroy_image(env->mlx, env->we_tex.img);
// 		if (env->ea_tex.img)
// 			mlx_destroy_image(env->mlx, env->ea_tex.img);

// 		if (env->win)
// 			mlx_destroy_window(env->mlx, env->win);
// 	}

// 	ft_gc_exit(EXIT_SUCCESS);
// 	return (0);
// }

int main(int argc, char **argv)
{
	t_game	env;

	if (argc != 2)
		ft_error("Use: ./cub3d <caminho/para/arquivo.cub>");
	
	check_file_extension(argv[1]);
	init_parse_data(&env);
	parse_scene_file(&env, argv[1]);

	init_game(&env);

	mlx_hook(env.win, 2, 1L<<0, key_press, &env);
	mlx_hook(env.win, 3, 1L<<1, key_release, &env);
	mlx_hook(env.win, 17, 0, close_win, &env);

	mlx_loop_hook(env.mlx, draw_loop, &env);
	mlx_loop(env.mlx);

	return (0);
}