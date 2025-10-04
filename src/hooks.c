#include "../include/cub3d.h"

int	key_press(int keycode, t_game *env)
{
	if (keycode == W)
		env->player.key_up =FALSE;
	if (keycode == S)
		env->player.key_down =FALSE;
	if (keycode == A)
		env->player.key_left =FALSE;
	if (keycode == D)
		env->player.key_right =FALSE;
	if (keycode == ESC)
		close_win(env);
	if (keycode == LEFT)
		env->player.left_rotate =FALSE;
	if (keycode == RIGHT)
		env->player.right_rotate =FALSE;
	return (0);
}

int	key_release(int keycode, t_game *env)
{
	if (keycode == W)
		env->player.key_up = FALSE;
	if (keycode == S)
		env->player.key_down = FALSE;
	if (keycode == A)
		env->player.key_left = FALSE;
	if (keycode == D)
		env->player.key_right = FALSE;
	if (keycode == LEFT)
		env->player.left_rotate = FALSE;
	if (keycode == RIGHT)
		env->player.right_rotate = FALSE;
	return (0);
}