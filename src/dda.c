/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller- <ekeller-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:51:07 by ekeller-          #+#    #+#             */
/*   Updated: 2025/10/10 10:51:13 by ekeller-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/cub3d.h"

/* ---------- camera build (dir/plane from your angle) ------------------- */

void	make_camera(t_game *e, t_vec *dir, t_vec *plane)
{
	dir->x = cos(e->player.angle);
	dir->y = sin(e->player.angle);
	plane->x = -dir->y * FOV_FACTOR;
	plane->y = dir->x * FOV_FACTOR;
}

/* ---------- per-column ray setup -------------------------------------- */

static void	set_delta(t_ray *r)
{
	if (fabs(r->dir.x) < 1e-12)
		r->delta.x = 1e30;
	else
		r->delta.x = fabs(1.0 / r->dir.x);
	if (fabs(r->dir.y) < 1e-12)
		r->delta.y = 1e30;
	else
		r->delta.y = fabs(1.0 / r->dir.y);
}

static void	define_side_step(t_ray *r, double px, double py)
{
	if (r->dir.x < 0.0)
	{
		r->step_x = -1;
		r->side.x = (px - r->mapx) * r->delta.x;
	}
	else
	{
		r->step_x = 1;
		r->side.x = (r->mapx + 1.0 - px) * r->delta.x;
	}
	if (r->dir.y < 0.0)
	{
		r->step_y = -1;
		r->side.y = (py - r->mapy) * r->delta.y;
	}
	else
	{
		r->step_y = 1;
		r->side.y = (r->mapy + 1.0 - py) * r->delta.y;
	}
}

//cam_x set pixel columns between -1 and 1. 
void	ray_setup(t_game *e, t_ray *r, t_vec v[2], int x)
{
	double	cam_x;
	double	px;
	double	py;

	cam_x = 2.0 * x / WIDTH - 1.0;
	r->dir.x = v[0].x + v[1].x * cam_x;
	r->dir.y = v[0].y + v[1].y * cam_x;
	px = e->player.x / TILE_SIZE;
	py = e->player.y / TILE_SIZE;
	r->mapx = px;
	r->mapy = py;
	set_delta(r);
	define_side_step(r, px, py);
	r->hit = 0;
}

/* ---------- step through grid (DDA) ----------------------------------- */

void	ray_dda(t_game *e, t_ray *r)
{
	while (r->hit == 0)
	{
		if (r->side.x < r->side.y)
		{
			r->side.x += r->delta.x;
			r->mapx += r->step_x;
			r->side_hit = 0;
		}
		else
		{
			r->side.y += r->delta.y;
			r->mapy += r->step_y;
			r->side_hit = 1;
		}
		if (map_wall(e, r->mapx, r->mapy))
			r->hit = 1;
	}
}
