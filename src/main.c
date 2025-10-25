/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 16:37:52 by acesar-m          #+#    #+#             */
/*   Updated: 2025/10/25 17:08:52 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_parse_data(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->parse.fd = -1;
}

int	main(int argc, char **argv)
{
	t_game	env;

	if (argc != 2)
	{
		ft_error("Use: ./cub3d <caminho/para/arquivo.cub>");
		return (1);
	}
	check_file_extension(argv[1]);
	init_parse_data(&env);
	parse_scene_file(&env, argv[1]);
	init_game(&env);
	mlx_hook(env.win, 2, 1L << 0, key_press, &env);
	mlx_hook(env.win, 3, 1L << 1, key_release, &env);
	mlx_hook(env.win, 17, 0, close_win, &env);
	mlx_loop_hook(env.mlx, render_loop, &env);
	mlx_loop(env.mlx);
	return (0);
}
