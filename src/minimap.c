/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller- <ekeller-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 16:37:58 by acesar-m          #+#    #+#             */
/*   Updated: 2025/10/13 13:26:45 by ekeller-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/cub3d.h"

static void	draw_minimap_tile(t_game *game, int map_x, int map_y, int color)
{
	int	start_x;
	int	start_y;
	int	x;
	int	y;
	int	tile_size;

	tile_size = TILE_SIZE * MINIMAP_SCALE;
	start_x = map_x * tile_size;
	start_y = map_y * tile_size;
	y = 0;
	while (y < tile_size)
	{
		x = 0;
		while (x < tile_size)
		{
			put_pixel(start_x + x + 10, start_y + y + 10, color, game);
			x++;
		}
		y++;
	}
}

static void	draw_minimap_player(t_game *game)
{
	int	player_x;
	int	player_y;
	int	size;
	int	x;
	int	y;

	size = 4;
	player_x = (game->player.x * MINIMAP_SCALE) - (size / 2);
	player_y = (game->player.y * MINIMAP_SCALE) - (size / 2);
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			put_pixel(player_x + x + 10, player_y + y + 10, 0xFF0000, game);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (game->map.grid[y] && game->map.grid[y][x])
		{
			if (game->map.grid[y][x] == '1')
				draw_minimap_tile(game, x, y, 0x404040);
			else if (game->map.grid[y][x] == '0' ||
					ft_strchr("NSEW", game->map.grid[y][x]))
				draw_minimap_tile(game, x, y, 0xEAEAEA);
			x++;
		}
		y++;
	}
	draw_minimap_player(game);
}
