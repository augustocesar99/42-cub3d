/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller- <ekeller-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:51:50 by ekeller-          #+#    #+#             */
/*   Updated: 2025/10/13 12:45:52 by ekeller-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
	env->player.x *= TILE_SIZE;
	env->player.y *= TILE_SIZE;
	init_player(&env->player);
	spawn(env);
	env->mlx = mlx_init();
	if (!env->mlx)
		ft_error("Falha ao inicializar a MiniLibX.");
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "cub3D");
	if (!env->win)
		ft_error("Falha ao criar a janela.");
	env->img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	if (!env->img)
		ft_error("Falha ao criar a imagem.");
	env->address = mlx_get_data_addr(env->img,
			&env->bpp, &env->size_line, &env->endian);
	if (load_all_textures(env))
		ft_error("Erro ao carregar texturas.");
}

void	init_player(t_player *player)
{
	player->key_down = FALSE;
	player->key_up = FALSE;
	player->key_left = FALSE;
	player->key_right = FALSE;
	player->left_rotate = FALSE;
	player->right_rotate = FALSE;
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
	ft_gc_free_all();
	exit(0);
}
