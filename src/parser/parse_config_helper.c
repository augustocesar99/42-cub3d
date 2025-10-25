/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_config_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:31:08 by acesar-m          #+#    #+#             */
/*   Updated: 2025/10/25 15:34:07 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_rgb_count(char **rgb_values)
{
	int	i;

	i = 0;
	while (rgb_values[i])
		i++;
	if (i != 3)
	{
		ft_free_split(rgb_values);
		ft_error("Cor RGB deve ter exatamente 3 valores (R,G,B).");
	}
}

void	set_rgb_component(t_rgb *color, int index, long val, char **rgb_values)
{
	if (val < 0 || val > 255)
	{
		ft_free_split(rgb_values);
		ft_error("Valor RGB fora do intervalo [0, 255].");
	}
	if (index == 0)
		color->r = (int)val;
	else if (index == 1)
		color->g = (int)val;
	else if (index == 2)
		color->b = (int)val;
}

void	set_element_bit(t_game *game, int mask, char *identifier)
{
	(void)identifier;
	if (game->parse.elements_found & mask)
		ft_error("Elemento de configuração duplicado.");
	game->parse.elements_found |= mask;
}

int	check_texture(t_game *game, char *line, char *str_content)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "NO\t", 3) == 0)
		return (set_element_bit(game, TEX_NO, "NO"),
			parse_texture_path(game, str_content, &game->no_tex), 1);
	if (ft_strncmp(line, "SO ", 3) == 0 || ft_strncmp(line, "SO\t", 3) == 0)
		return (set_element_bit(game, TEX_SO, "SO"),
			parse_texture_path(game, str_content, &game->so_tex), 1);
	if (ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "WE\t", 3) == 0)
		return (set_element_bit(game, TEX_WE, "WE"),
			parse_texture_path(game, str_content, &game->we_tex), 1);
	if (ft_strncmp(line, "EA ", 3) == 0 || ft_strncmp(line, "EA\t", 3) == 0)
		return (set_element_bit(game, TEX_EA, "EA"),
			parse_texture_path(game, str_content, &game->ea_tex), 1);
	return (0);
}

int	check_color(t_game *game, char *line, char *str_content)
{
	if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "F\t", 2) == 0)
		return (set_element_bit(game, COLOR_F, "F"),
			parse_rgb(game, str_content, &game->floor), 1);
	if (ft_strncmp(line, "C ", 2) == 0 || ft_strncmp(line, "C\t", 2) == 0)
		return (set_element_bit(game, COLOR_C, "C"),
			parse_rgb(game, str_content, &game->ceiling), 1);
	return (0);
}
