/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 16:38:34 by acesar-m          #+#    #+#             */
/*   Updated: 2025/11/06 13:00:57 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	save_player_data(t_game *game, char direction, int x, int y)
{
	const t_dir	dirs[4] = {{'N', 0, -1, 0.66, 0}, {'S', 0, 1, -0.66, 0},
	{'W', -1, 0, 0, -0.66}, {'E', 1, 0, 0, 0.66}};
	int			i;

	if (game->player.dir_x || game->player.dir_y)
		ft_error("[MAP ERROR] Map must have only one initial position.");
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

static void	process_char(t_game *game, t_validate_data *data)
{
	if (data->c == '0' || data->c == '1' || data->c == ' ')
		data->clean[data->x] = data->c;
	else if (ft_strchr("NSEW", data->c))
		data->clean[data->x] = save_player_data(game, data->c,
				data->x, data->y);
	else
		ft_error("[MAP ERROR] Invalid character found in map.");
}

static char	*validate_and_clean_line(t_game *game, char *raw_line, int y)
{
	t_validate_data	data;
	int				len;

	init_validate_data(&data, raw_line, y);
	len = ft_strlen(raw_line);
	while (data.x < len && raw_line[data.x])
	{
		data.c = raw_line[data.x];
		process_char(game, &data);
		data.x++;
	}
	data.clean[data.x] = '\0';
	return (data.clean);
}

void	validate_map_integrity(t_game *game)
{
	int	y;
	int	x;

	if (game->player.dir_x == 0 && game->player.dir_y == 0)
		ft_error("[MAP ERROR] Map must include initil player position.");
	y = 0;
	while (y < game->map.height && game->map.grid[y])
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (game->map.grid[y][x] == '0'
				|| ft_strchr("NSEW", game->map.grid[y][x]))
				validate_position(game, y, x);
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
		ft_error("[PARSE ERROR] Insufficient configurations before map.");
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
