/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:53:05 by ekeller-          #+#    #+#             */
/*   Updated: 2025/10/11 16:06:34 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	tex_get_pixel(const t_texture *t, int x, int y)
{
	char	*p;

	if (!t || !t->addr)
		return (0);
	if (x < 0 || y < 0 || x >= t->width || y >= t->height)
		return (0);
	p = (char *)t->addr;
	p += y * t->line_len + x * (t->bpp / 8);
	return (*(int *)p);
}

t_texture	*pick_tex(t_game *e, t_ray *r)
{
	if (r->side_hit == 0)
	{
		if (r->dir_x > 0.0)
			return (&e->we_tex);
		return (&e->ea_tex);
	}
	if (r->dir_y > 0.0)
		return (&e->no_tex);
	return (&e->so_tex);
}

void	draw_textured_column(t_game *e, int x, t_drawcol *d, t_texture *tx)
{
	int	y;
	int	ty;
	int	color;

	y = d->start;
	while (y <= d->end)
	{
		ty = (int)d->tex_pos;
		if (ty < 0)
			ty = 0;
		if (ty >= tx->height)
			ty = tx->height - 1;
		color = tex_get_pixel(tx, d->tex_x, ty);
		put_pixel(x, y, color, e);
		d->tex_pos += d->step;
		y++;
	}
}
