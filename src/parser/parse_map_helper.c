/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:00:00 by acesar-m          #+#    #+#             */
/*   Updated: 2025/11/06 12:58:37 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	is_on_border(t_game *game, int y, int x)
{
	if (y == 0 || y == game->map.height - 1)
		return (TRUE);
	if (x == 0 || x == (int)ft_strlen(game->map.grid[y]) - 1)
		return (TRUE);
	return (FALSE);
}

t_bool	check_all_neighbors(t_game *game, int y, int x)
{
	if (is_unsafe_neighbor(game, y, x + 1))
		return (TRUE);
	if (is_unsafe_neighbor(game, y, x - 1))
		return (TRUE);
	if (is_unsafe_neighbor(game, y + 1, x))
		return (TRUE);
	if (is_unsafe_neighbor(game, y - 1, x))
		return (TRUE);
	if (is_unsafe_neighbor(game, y - 1, x - 1))
		return (TRUE);
	if (is_unsafe_neighbor(game, y - 1, x + 1))
		return (TRUE);
	if (is_unsafe_neighbor(game, y + 1, x - 1))
		return (TRUE);
	if (is_unsafe_neighbor(game, y + 1, x + 1))
		return (TRUE);
	return (FALSE);
}

void	validate_position(t_game *game, int y, int x)
{
	if (is_on_border(game, y, x))
		ft_error("[MAP ERROR] Players position or empty space at the border.");
	if (check_all_neighbors(game, y, x))
		ft_error("[MAP ERROR] Map not surrounded by walls.");
}

void	remove_line_endings(char *line, int *len)
{
	if (*len > 0 && line[*len - 1] == '\n')
	{
		line[*len - 1] = '\0';
		(*len)--;
	}
	if (*len > 0 && line[*len - 1] == '\r')
	{
		line[*len - 1] = '\0';
		(*len)--;
	}
}
