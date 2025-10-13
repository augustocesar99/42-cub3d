/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller- <ekeller-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 16:38:43 by acesar-m          #+#    #+#             */
/*   Updated: 2025/10/13 11:28:32 by ekeller-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"

static char	*skip_spaces(char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	return (line);
}

static void	parse_rgb(t_game *game, char *str, t_rgb *color_struct)
{
	char	**rgb_values;
	int		i;
	long	val;

	(void)game;
	rgb_values = ft_split(str, ',');
	if (!rgb_values)
		ft_error("Erro de alocação ao processar cor RGB.");
	
	i = 0;
	while (rgb_values[i])
		i++;
	if (i != 3)
	{
		ft_free_split(rgb_values);
		ft_error("Cor RGB deve ter exatamente 3 valores (R,G,B).");
	}

	i = -1;
	while (rgb_values[++i])
	{
		val = ft_atol(rgb_values[i]);
		if (val < 0 || val > 255)
		{
			ft_free_split(rgb_values);
			ft_error("Valor RGB fora do intervalo [0, 255].");
		}
		if (i == 0)
			color_struct->r = (int)val;
		else if (i == 1)
			color_struct->g = (int)val;
		else if (i == 2)
			color_struct->b = (int)val;
	}

	color_struct->value = (color_struct->r << 16 | color_struct->g << 8 | color_struct->b);
	ft_free_split(rgb_values);
}

static void	parse_texture_path(t_game *game, char *line, t_texture *tex_struct)
{
	char *path_end;
	char *temp;

	(void)game;
	path_end = skip_spaces(line);
	if (*path_end == '\0')
		ft_error("Caminho da textura vazio.");

	temp = ft_strdup_cub(path_end);
	if (!temp)
		ft_error("Erro de alocação para o caminho da textura.");

	int len = ft_strlen(temp);
	while (len > 0 && (temp[len-1] == ' ' || temp[len-1] == '\t' || temp[len-1] == '\n'))
	{
		temp[len-1] = '\0';
		len--;
	}

	tex_struct->path = temp;
}

static void	set_element_bit(t_game *game, int mask, char *identifier)
{
	(void)identifier;
	if (game->parse.elements_found & mask)
		ft_error("Elemento de configuração duplicado.");
	game->parse.elements_found |= mask;
}

int	extract_element(t_game *game, char *line)
{
	char	*str_content;

	str_content = skip_spaces(line + 2);

	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "NO\t", 3) == 0)
	{
		set_element_bit(game, TEX_NO, "NO");
		parse_texture_path(game, str_content, &game->no_tex);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0 || ft_strncmp(line, "SO\t", 3) == 0)
	{
		set_element_bit(game, TEX_SO, "SO");
		parse_texture_path(game, str_content, &game->so_tex);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "WE\t", 3) == 0)
	{
		set_element_bit(game, TEX_WE, "WE");
		parse_texture_path(game, str_content, &game->we_tex);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0 || ft_strncmp(line, "EA\t", 3) == 0)
	{
		set_element_bit(game, TEX_EA, "EA");
		parse_texture_path(game, str_content, &game->ea_tex);
	}
	else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "F\t", 2) == 0)
	{
		set_element_bit(game, COLOR_F, "F");
		parse_rgb(game, str_content, &game->floor);
	}
	else if (ft_strncmp(line, "C ", 2) == 0 || ft_strncmp(line, "C\t", 2) == 0)
	{
		set_element_bit(game, COLOR_C, "C");
		parse_rgb(game, str_content, &game->ceiling);
	}
	else
	{
		return (0);
	}
	return (1);
}
