/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:19:46 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/11/07 17:47:28 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//compute the perpendicular distance from player to wall.
static void	compute_dist(t_game *e, t_ray *r)
{
	double	px;
	double	py;

	px = e->player.x / TILE_SIZE;
	py = e->player.y / TILE_SIZE;
	if (r->side_hit == 0)
		r->dist = (r->mapx - px + (1 - r->step_x) / 2.0) / r->dir_x;
	else
		r->dist = (r->mapy - py + (1 - r->step_y) / 2.0) / r->dir_y;
}

//calculate start and end positions of the 3d wall and its height,
//fitting it in the screen boundaries. 
static void	compute_column_bounds(t_ray *r, t_drawcol *d)
{
	d->line_h = (HEIGHT / r->dist);
	d->start = -d->line_h / 2 + HEIGHT / 2;
	if (d->start < 0)
		d->start = 0;
	d->end = d->line_h / 2 + HEIGHT / 2;
	if (d->end >= HEIGHT)
		d->end = HEIGHT - 1;
}

static double	wall_x_coord(t_game *e, t_ray *r)
{
	double	wx;

	if (r->side_hit == 0)
		wx = e->player.y / TILE_SIZE + r->dist * r->dir_y;
	else
		wx = e->player.x / TILE_SIZE + r->dist * r->dir_x;
	return (wx - floor(wx));
}

//Selects the appropriate wall texture based on which face was
//hit and calculates texture mapping parameters.
static void	prep_tex_params(t_game *e, t_ray *r, t_drawcol *d, t_texture **tx)
{
	double	wx;

	*tx = pick_tex(e, r);
	wx = wall_x_coord(e, r);
	d->tex_x = (wx * (*tx)->width);
	if (r->side_hit == 0 && r->dir_x > 0.0)
		d->tex_x = (*tx)->width - d->tex_x - 1;
	if (r->side_hit == 1 && r->dir_y < 0.0)
		d->tex_x = (*tx)->width - d->tex_x - 1;
	d->step = 1.0 * (*tx)->height / d->line_h;
	d->tex_pos = (d->start - HEIGHT / 2 + d->line_h / 2) * d->step;
}

/* ---------- main loop: draw one frame --------------------------------- */
int	render_loop(t_game *e)
{
	int			x;
	t_ray		r;
	t_drawcol	d;
	t_texture	*tx;

	move_player(e);
	draw_background(e);
	make_camera(e);
	x = 0;
	while (x < WIDTH)
	{
		ray_setup(e, &r, x);
		ray_dda(e, &r);
		compute_dist(e, &r);
		compute_column_bounds(&r, &d);
		prep_tex_params(e, &r, &d, &tx);
		draw_textured_column(e, x, &d, tx);
		x++;
	}
	draw_minimap(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}
