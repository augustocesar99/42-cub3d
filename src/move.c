/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller- <ekeller-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:52:29 by ekeller-          #+#    #+#             */
/*   Updated: 2025/10/13 13:25:23 by ekeller-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/cub3d.h"

void	rotate(t_game *env)
{
	if (env->player.left_rotate)
		env->player.angle -= ANGLE_SPEED;
	if (env->player.right_rotate)
		env->player.angle += ANGLE_SPEED;
	if (env->player.angle > 2 * PI)
		env->player.angle -= 2 * PI;
	if (env->player.angle < 0)
		env->player.angle = 2 * PI;
}

void	move(t_game *env)
{
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(env->player.angle);
	sin_angle = sin(env->player.angle);
	if (env->player.key_up)
	{
		env->player.x += cos_angle * SPEED;
		env->player.y += sin_angle * SPEED;
	}
	if (env->player.key_down)
	{
		env->player.x -= cos_angle * SPEED;
		env->player.y -= sin_angle * SPEED;
	}
	if (env->player.key_left)
	{
		env->player.x += sin_angle * SPEED;
		env->player.y -= cos_angle * SPEED;
	}
	if (env->player.key_right)
	{
		env->player.x -= sin_angle * SPEED;
		env->player.y += cos_angle * SPEED;
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
