/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller- <ekeller-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:52:03 by ekeller-          #+#    #+#             */
/*   Updated: 2025/10/10 10:52:05 by ekeller-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/cub3d.h"

int	main(void)
{
	t_game	env;

	init_game(&env);
	mlx_hook(env.win, 2, 1L << 0, key_press, &env);
	mlx_hook(env.win, 3, 1L << 1, key_release, &env);
	mlx_hook(env.win, 17, 0, close_win, &env);
	mlx_loop_hook(env.mlx, draw_loop, &env);
	mlx_loop(env.mlx);
	return (0);
}
