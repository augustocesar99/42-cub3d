/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 16:38:25 by acesar-m          #+#    #+#             */
/*   Updated: 2025/11/06 17:24:21 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_all_elements_found(t_game *game)
{
	if (game->parse.elements_found != ALL_ELEMENTS)
	{
		ft_error("Wrong config: elements missing\
			(NO, SO, WE, EA, F or C).");
	}
}

static void	process_line(t_game *game, char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	if (ft_strlen(line) == 0 || (*line == '\n' && ft_strlen(line) == 1))
	{
		if (game->parse.map_started)
			ft_error("[MAP ERROR] Empty line found in the map.");
		return ;
	}
	if (game->parse.elements_found != ALL_ELEMENTS)
	{
		if (extract_element(game, line))
			return ;
	}
	read_map_line(game, line);
}

static char	*get_next_line_gc(int fd)
{
	char	*line;
	char	*tracked_line;
	size_t	len;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	tracked_line = ft_malloc(len + 1);
	ft_memcpy(tracked_line, line, len + 1);
	free(line);
	return (tracked_line);
}

static void	cleanup_gnl(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
	}
}

void	parse_scene_file(t_game *game, char *filepath)
{
	char	*line;

	game->parse.fd = open(filepath, O_RDONLY);
	if (game->parse.fd < 0)
		ft_error("It was not possible to open the map.");
	while (1)
	{
		line = get_next_line_gc(game->parse.fd);
		if (!line)
			break ;
		game->parse.line_number++;
		process_line(game, line);
		ft_free(line);
	}
	cleanup_gnl(game->parse.fd);
	close(game->parse.fd);
	game->parse.fd = -1;
	check_all_elements_found(game);
	if (!game->map.grid)
		ft_error("The file does not contain a map.");
	validate_map_integrity(game);
}
