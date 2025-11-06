/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:20:16 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/11/06 11:20:18 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	load_texture(t_game *game, t_texture *texture)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, texture->path,
			&texture->width, &texture->height);
	if (!texture->img)
		return (1);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_len, &texture->endian);
	if (!texture->addr)
		return (1);
	return (0);
}

int	load_all_textures(t_game *game)
{
	if (load_texture(game, &game->no_tex))
		return (1);
	if (load_texture(game, &game->so_tex))
		return (1);
	if (load_texture(game, &game->we_tex))
		return (1);
	if (load_texture(game, &game->ea_tex))
		return (1);
	return (0);
}

void	destroy_all_textures(t_game *game)
{
	if (game->no_tex.img)
		mlx_destroy_image(game->mlx, game->no_tex.img);
	if (game->so_tex.img)
		mlx_destroy_image(game->mlx, game->so_tex.img);
	if (game->we_tex.img)
		mlx_destroy_image(game->mlx, game->we_tex.img);
	if (game->ea_tex.img)
		mlx_destroy_image(game->mlx, game->ea_tex.img);
}
