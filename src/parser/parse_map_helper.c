/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:00:00 by acesar-m          #+#    #+#             */
/*   Updated: 2025/10/25 16:05:22 by acesar-m         ###   ########.fr       */
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
		ft_error("[MAP ERROR] Posicao do jogador ou espaco vazio na borda.");
	if (check_all_neighbors(game, y, x))
		ft_error("[MAP ERROR] Mapa nao esta cercado por paredes.");
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
