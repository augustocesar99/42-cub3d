/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:04:22 by acesar-m          #+#    #+#             */
/*   Updated: 2025/10/25 16:05:26 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_validate_data(t_validate_data *data, char *raw, int y)
{
	int	len;

	len = ft_strlen(raw);
	remove_line_endings(raw, &len);
	data->clean = (char *)ft_malloc(len + 1);
	if (!data->clean)
		ft_error("[ALLOC ERROR] Falha na alocacao da linha do mapa.");
	data->x = 0;
	data->y = y;
}

t_bool	is_unsafe_neighbor(t_game *game, int y, int x)
{
	if (y < 0 || y >= game->map.height)
		return (TRUE);
	if (!game->map.grid[y] || x < 0
		|| x >= (int)ft_strlen(game->map.grid[y]))
		return (TRUE);
	if (game->map.grid[y][x] == ' ')
		return (TRUE);
	return (FALSE);
}
