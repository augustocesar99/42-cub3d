/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 16:38:34 by acesar-m          #+#    #+#             */
/*   Updated: 2025/10/12 16:40:48 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	save_player_data(t_game *game, char direction, int x, int y)
{
	const t_dir dirs[] = {
		{'N', 0, -1, 0.66, 0},
		{'S', 0,  1, -0.66, 0},
		{'W', -1, 0, 0, -0.66},
		{'E', 1,  0, 0, 0.66}
	};
	int	i;

	if (game->player.dir_x || game->player.dir_y)
		ft_error("[MAP ERROR] O mapa deve conter apenas uma posição inicial do jogador (N, S, E ou W).");

	game->player.x = (double)x + 0.5;
	game->player.y = (double)y + 0.5;
	game->spawn_side = direction;

	i = 0;
	while (i < 4)
	{
		if (dirs[i].c == direction)
		{
			game->player.dir_x = dirs[i].dir_x;
			game->player.dir_y = dirs[i].dir_y;
			game->player.plane_x = dirs[i].plane_x;
			game->player.plane_y = dirs[i].plane_y;
			break ;
		}
		i++;
	}
	return ('0');
}

static char	*validate_and_clean_line(t_game *game, char *raw_line, int y)
{
	char	*clean_line;
	int		x;
	int		len;

	len = ft_strlen(raw_line);
	if (len > 0 && raw_line[len - 1] == '\n') {
		raw_line[len - 1] = '\0';
		len--;
	}
	if (len > 0 && raw_line[len - 1] == '\r') {
		raw_line[len - 1] = '\0';
		len--;
	}

	clean_line = (char *)ft_malloc(len + 1);
	if (!clean_line)
		ft_error("[ALLOC ERROR] Falha na alocação da linha do mapa.");

	x = 0;
	while (x < len && raw_line[x])
	{
		if (raw_line[x] == '0' || raw_line[x] == '1' || raw_line[x] == ' ')
			clean_line[x] = raw_line[x];
		else if (ft_strchr("NSEW", raw_line[x]))
			clean_line[x] = save_player_data(game, raw_line[x], x, y);
		else
			ft_error("[MAP ERROR] Caractere inválido encontrado no mapa.");
		x++;
	}
	clean_line[x] = '\0';
	
	return (clean_line);
}

static t_bool is_unsafe_neighbor(t_game *game, int y, int x)
{
	if (y < 0 || y >= game->map.height)
		return (TRUE);

		if (!game->map.grid[y] || x < 0 || x >= (int)ft_strlen(game->map.grid[y]))
		return (TRUE);

	if (game->map.grid[y][x] == ' ')
		return (TRUE);
	
	return (FALSE);
}

void validate_map_integrity(t_game *game)
{
	int y;
	int x;

	if (game->player.dir_x == 0 && game->player.dir_y == 0)
		ft_error("[MAP ERROR] O mapa deve ter uma posição inicial de jogador (N, S, E ou W).");

	y = 0;
	while (y < game->map.height && game->map.grid[y])
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (game->map.grid[y][x] == '0' || ft_strchr("NSEW", game->map.grid[y][x]))
			{
				if (y == 0 || y == game->map.height - 1 || x == 0 || 
					x == (int)ft_strlen(game->map.grid[y]) - 1)
					ft_error("[MAP ERROR] Posição do jogador ou espaço vazio na borda do mapa.");
				if (is_unsafe_neighbor(game, y, x + 1) ||
					is_unsafe_neighbor(game, y, x - 1) ||
					is_unsafe_neighbor(game, y + 1, x) ||
					is_unsafe_neighbor(game, y - 1, x) ||
					is_unsafe_neighbor(game, y - 1, x - 1) ||
					is_unsafe_neighbor(game, y - 1, x + 1) ||
					is_unsafe_neighbor(game, y + 1, x - 1) ||
					is_unsafe_neighbor(game, y + 1, x + 1))
				{
					ft_error("[MAP ERROR] O mapa não está completamente cercado por paredes.");
				}
			}
			x++;
		}
		y++;
	}
}

void	read_map_line(t_game *game, char *raw_line)
{
	char	*clean_line;
	int		new_height;
	char	**new_grid;
	int		i;

	if (game->parse.elements_found != ALL_ELEMENTS)
		ft_error("[PARSE ERROR] Configurações insuficientes antes da linha de mapa.");

	game->parse.map_started = 1;
	clean_line = validate_and_clean_line(game, raw_line, game->map.height);
	new_height = game->map.height + 1;
	new_grid = (char **)ft_malloc(sizeof(char *) * (new_height + 1));
	i = 0;
	while (i < game->map.height)
	{
		new_grid[i] = game->map.grid[i];
		i++;
	}
	new_grid[i] = clean_line;
	new_grid[i + 1] = NULL;
	game->map.grid = new_grid;
	game->map.height = new_height;
	if ((int)ft_strlen(clean_line) > game->map.width)
		game->map.width = ft_strlen(clean_line);
}
