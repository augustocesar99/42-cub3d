/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:04:22 by acesar-m          #+#    #+#             */
/*   Updated: 2025/11/06 12:59:03 by ekeller-@st      ###   ########.fr       */
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
		ft_error("[ALLOC ERROR] Failed allocation in map line.");
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
