/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:52:29 by ekeller-          #+#    #+#             */
/*   Updated: 2025/11/06 12:17:49 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// void	move_player(t_game *env)
// {
// 	float	old_x;
// 	float	old_y;

// 	old_x = env->player.x;
// 	old_y = env->player.y;
// 	rotate(env);
// 	move(env);
// 	if (map_wall(env, env->player.x / TILE_SIZE, env->player.y / TILE_SIZE))
// 	{
// 		env->player.x = old_x;
// 		env->player.y = old_y;
// 	}
// }

static int	check_collision_with_margin(t_game *env, float x, float y)
{
    int	margin;

    margin = 10;
    if (map_wall(env, (x + margin) / TILE_SIZE, (y + margin) / TILE_SIZE))
        return (1);
    if (map_wall(env, (x - margin) / TILE_SIZE, (y - margin) / TILE_SIZE))
        return (1);
    if (map_wall(env, (x + margin) / TILE_SIZE, (y - margin) / TILE_SIZE))
        return (1);
    if (map_wall(env, (x - margin) / TILE_SIZE, (y + margin) / TILE_SIZE))
        return (1);
    return (0);
}

//first if check if player is moving diagonally with both y and x changing.
//second if checks movement in the x axis(n and s walls)
//third if checks movement on the y axis
void	move_player(t_game *env)
{
    float	old_x;
    float	old_y;
    float	new_x;
    float	new_y;

    old_x = env->player.x;
    old_y = env->player.y;
    rotate(env);
    move(env);
    new_x = env->player.x;
    new_y = env->player.y;
    if (check_collision_with_margin(env, new_x, new_y))
    {
        env->player.x = old_x;
        env->player.y = old_y;
        if (!check_collision_with_margin(env, new_x, old_y))
            env->player.x = new_x;
        else if (!check_collision_with_margin(env, old_x, new_y))
            env->player.y = new_y;
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
