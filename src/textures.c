/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller- <ekeller-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:53:05 by ekeller-          #+#    #+#             */
/*   Updated: 2025/10/10 10:53:07 by ekeller-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/cub3d.h"

int	load_texture_path(t_game *e, t_texture *t, const char *path)
{
	int	w;
	int	h;

	if (!path || !*path)
		return (1);
	set_tex_zero(t);
	t->img = mlx_xpm_file_to_image(e->mlx, (char *)path, &w, &h);
	if (!t->img)
	{
		ft_printf("texture image failed\n");
		return (1);
	}
	t->addr = mlx_get_data_addr(t->img,
			&t->bpp, &t->line_len, &t->endian);
	if (!t->addr)
	{
		ft_printf("texture address failed\n");
		mlx_destroy_image(e->mlx, t->img);
		set_tex_zero(t);
		return (1);
	}
	t->w = w;
	t->h = h;
	return (0);
}

/* Returns non-zero on error; destroys any previously loaded textures */
int	load_all_textures(t_game *e)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		set_tex_zero(&e->tex[i]);
		i++;
	}
	if (load_texture_path(e, &e->tex[TEX_NO], e->no_tex.path))
		return (destroy_all_textures(e), 1);
	if (load_texture_path(e, &e->tex[TEX_SO], e->so_tex.path))
		return (destroy_all_textures(e), 1);
	if (load_texture_path(e, &e->tex[TEX_WE], e->we_tex.path))
		return (destroy_all_textures(e), 1);
	if (load_texture_path(e, &e->tex[TEX_EA], e->ea_tex.path))
		return (destroy_all_textures(e), 1);
	return (0);
}

int	pick_tex(t_ray *r)
{
	if (r->side_hit == 0)
	{
		if (r->dir.x > 0.0)
			return (TEX_WE);
		return (TEX_EA);
	}
	if (r->dir.y > 0.0)
		return (TEX_NO);
	return (TEX_SO);
}

void	draw_textured_column(t_game *e, int x, t_drawcol *d, t_texture *tx)
{
	int	y;
	int	ty;
	int	color;

	y = d->start;
	while (y <= d->end)
	{
		ty = d->tex_pos;
		if (ty < 0)
			ty = 0;
		if (ty >= tx->h)
			ty = tx->h - 1;
		color = tex_get_pixel(tx, d->tex_x, ty);
		put_pixel(x, y, color, e);
		d->tex_pos += d->step;
		y++;
	}
}
