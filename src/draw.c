/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 16:38:11 by acesar-m          #+#    #+#             */
/*   Updated: 2025/10/12 16:38:13 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	put_pixel(int x, int y, int color, t_game *env)
{
	char	*pxl;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pxl = env->address +(y * env->size_line
				+ x * (env->bpp / 8));
		*(unsigned int *)pxl = color;
	}
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

void draw_line(t_game *env, float start_x, int i)
{
	float	ray_x;
	float	ray_y;
	float	dist;
	float	corrected;
	float	plane;
	float	line_h;
	int		start_y;
	int		end;
	
	ray_x = env->player.x;
	ray_y = env->player.y;
	while (!map_wall(env, (int)(ray_x / TILE_SIZE), (int)(ray_y / TILE_SIZE)))
	{
		ray_x += cos(start_x);
		ray_y += sin(start_x);
	}
	dist = distance(ray_x - env->player.x, ray_y - env->player.y);
	corrected = dist * cosf(start_x - env->player.angle);
	if (corrected < 0.001)
		corrected = 0.001;
	plane = (float)WIDTH / 2.0 / tanf(PI / 3.0 * 0.5);
	line_h = (int)((float)TILE_SIZE * plane / corrected);
	start_y = (HEIGHT - line_h) / 2;
	if (start_y < 0)
		start_y = 0;
	end = start_y + line_h;
	if (end > HEIGHT)
		end = HEIGHT;

	while(start_y < end)
	{
		put_pixel(i, start_y, 0x00AAFF, env);
		start_y++;
	}
}
