/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 16:38:43 by acesar-m          #+#    #+#             */
/*   Updated: 2025/10/25 15:34:04 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*skip_spaces(char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	return (line);
}

void	parse_rgb(t_game *game, char *str, t_rgb *color_struct)
{
	char	**rgb_values;
	int		i;

	(void)game;
	rgb_values = ft_split(str, ',');
	if (!rgb_values)
		ft_error("Erro de alocação ao processar cor RGB.");
	validate_rgb_count(rgb_values);
	i = -1;
	while (rgb_values[++i])
		set_rgb_component(color_struct, i, ft_atol(rgb_values[i]), rgb_values);
	color_struct->value = (color_struct->r << 16
			| color_struct->g << 8 | color_struct->b);
	ft_free_split(rgb_values);
}

void	parse_texture_path(t_game *game, char *line, t_texture *tex_struct)
{
	char	*path_end;
	char	*temp;
	int		len;

	(void)game;
	path_end = skip_spaces(line);
	if (*path_end == '\0')
		ft_error("Caminho da textura vazio.");
	temp = ft_strdup_cub(path_end);
	if (!temp)
		ft_error("Erro de alocação para o caminho da textura.");
	len = ft_strlen(temp);
	while (len > 0 && (temp[len - 1] == ' ' || temp[len - 1] == '\t'
			|| temp[len - 1] == '\n'))
	{
		temp[len - 1] = '\0';
		len--;
	}
	tex_struct->path = temp;
}

int	extract_element(t_game *game, char *line)
{
	char	*str_content;

	str_content = skip_spaces(line + 2);
	if (check_texture(game, line, str_content))
		return (1);
	if (check_color(game, line, str_content))
		return (1);
	return (0);
}
