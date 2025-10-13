/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller- <ekeller-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:51:07 by ekeller-          #+#    #+#             */
/*   Updated: 2025/10/13 13:22:39 by ekeller-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/cub3d.h"

/* ---------- camera build (dir/plane from your angle) ------------------- */

void	make_camera(t_game *e)
{
	e->player.dir_x = cos(e->player.angle);
	e->player.dir_y = sin(e->player.angle);
	e->player.plane_x = -e->player.dir_y * FOV_FACTOR;
	e->player.plane_y = e->player.dir_x * FOV_FACTOR;
}

/* ---------- per-column ray setup -------------------------------------- */

static void	set_delta(t_ray *r)
{
	if (fabs(r->dir_x) < 1e-12)
		r->delta_x = 1e30;
	else
		r->delta_x = fabs(1.0 / r->dir_x);
	if (fabs(r->dir_y) < 1e-12)
		r->delta_y = 1e30;
	else
		r->delta_y = fabs(1.0 / r->dir_y);
}

static void	define_side_step(t_ray *r, double px, double py)
{
	if (r->dir_x < 0.0)
	{
		r->step_x = -1;
		r->side_x = (px - r->mapx) * r->delta_x;
	}
	else
	{
		r->step_x = 1;
		r->side_x = (r->mapx + 1.0 - px) * r->delta_x;
	}
	if (r->dir_y < 0.0)
	{
		r->step_y = -1;
		r->side_y = (py - r->mapy) * r->delta_y;
	}
	else
	{
		r->step_y = 1;
		r->side_y = (r->mapy + 1.0 - py) * r->delta_y;
	}
}

//cam_x set pixel columns between -1 and 1. 
void	ray_setup(t_game *e, t_ray *r, int x)
{
	double	cam_x;
	double	px;
	double	py;

	cam_x = 2.0 * x / WIDTH - 1.0;
	r->dir_x = e->player.dir_x + e->player.plane_x * cam_x;
	r->dir_y = e->player.dir_y + e->player.plane_y * cam_x;
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
		if (r->side_x < r->side_y)
		{
			r->side_x += r->delta_x;
			r->mapx += r->step_x;
			r->side_hit = 0;
		}
		else
		{
			r->side_y += r->delta_y;
			r->mapy += r->step_y;
			r->side_hit = 1;
		}
		if (map_wall(e, r->mapx, r->mapy))
			r->hit = 1;
	}
}
