#include "cub3d.h"

static void check_all_elements_found(t_game *game)
{
	if (game->parse.elements_found != ALL_ELEMENTS)
	ft_error("Configuração incompleta: faltam elementos (NO, SO, WE, EA, F ou C).");
}

static void process_line(t_game *game, char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;

	if (ft_strlen(line) == 0 || (*line == '\n' && ft_strlen(line) == 1))
		return;

	if (game->parse.elements_found != ALL_ELEMENTS)
	{
		if (extract_element(game, line))
			return;
	}
	read_map_line(game, line);
}

void	parse_scene_file(t_game *game, char *filepath)
{
	char	*line;

	game->parse.fd = open(filepath, O_RDONLY);
		if (game->parse.fd < 0)
		ft_error("Não foi possível abrir o arquivo de cena.");

	while (1)
	{
		line = get_next_line(game->parse.fd);
		if (!line)
			break;
		game->parse.line_number++;
		process_line(game, line);
		ft_free(line);
	}
	close(game->parse.fd);
	game->parse.fd = -1;
	check_all_elements_found(game);
	if (!game->map.grid)
		ft_error("O arquivo não contém um mapa."); 
	validate_map_integrity(game);
}