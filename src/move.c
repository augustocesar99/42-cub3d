/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller- <ekeller-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:52:09 by ekeller-          #+#    #+#             */
/*   Updated: 2025/10/10 10:52:11 by ekeller-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/cub3d.h"

void	put_pixel(int x, int y, int color, t_game *env)
{
	char	*pxl;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pxl = env->address +(y * env->size_line
				+ x * (env->bpp / 8));
		*(unsigned int *)pxl = color;
	}
}

void	rotate(t_game *env)
{
	if (env->player.left_rotate)
		env->player.angle -= ANGLE_SPEED;
	if (env->player.right_rotate)
		env->player.angle += ANGLE_SPEED;
	if (env->player.angle > 2 * PI)
		env->player.angle = 0;
	if (env->player.angle < 0)
		env->player.angle = 2 * PI;
}

void	move(t_game *env)
{
	if (env->player.key_up)
	{
		env->player.x += cos(env->player.angle) * SPEED;
		env->player.y += sin(env->player.angle) * SPEED;
	}
	if (env->player.key_down)
	{
		env->player.x -= cos(env->player.angle) * SPEED;
		env->player.y -= sin(env->player.angle) * SPEED;
	}
	if (env->player.key_left)
	{
		env->player.x += sin(env->player.angle) * SPEED;
		env->player.y -= cos(env->player.angle) * SPEED;
	}
	if (env->player.key_right)
	{
		env->player.x -= sin(env->player.angle) * SPEED;
		env->player.y += cos(env->player.angle) * SPEED;
	}
}

void	move_player(t_game *env)
{
	float	old_x;
	float	old_y;

	old_x = env->player.x;
	old_y = env->player.y;
	rotate(env);
	move(env);
	if (map_wall(env, env->player.x / TILE_SIZE, env->player.y / TILE_SIZE))
	{
		env->player.x = old_x;
		env->player.y = old_y;
	}
}

char	**get_map(void)
{
	char	**map;

	map = malloc(sizeof(char *) * 10);
	map[0] = "1111111111111";
	map[1] = "1010000000001";
	map[2] = "1010000000001";
	map[3] = "1000001000001";
	map[4] = "1000000000001";
	map[5] = "1000000000001";
	map[6] = "1000011100001";
	map[7] = "100001 100001";
	map[8] = "111111 111111";
	map[9] = NULL;
	return (map);
}
