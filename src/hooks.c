/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller- <ekeller-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:51:41 by ekeller-          #+#    #+#             */
/*   Updated: 2025/10/10 10:51:43 by ekeller-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/cub3d.h"

int	key_press(int keycode, t_game *env)
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
	if (keycode == LEFT)
		env->player.left_rotate = true;
	if (keycode == RIGHT)
		env->player.right_rotate = true;
	return (0);
}

int	key_release(int keycode, t_game *env)
{
	if (keycode == W)
		env->player.key_up = false;
	if (keycode == S)
		env->player.key_down = false;
	if (keycode == A)
		env->player.key_left = false;
	if (keycode == D)
		env->player.key_right = false;
	if (keycode == LEFT)
		env->player.left_rotate = false;
	if (keycode == RIGHT)
		env->player.right_rotate = false;
	return (0);
}
