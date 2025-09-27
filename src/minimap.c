#include "../include/cub3d.h"

void	put_pixel_minimap(int x, int y, int color, t_minimap *env)
{
	char	*pxl;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pxl = env->address +(y * env->size_line
			+ x * (env->bpp / 8));
		*(unsigned int *)pxl = color;
	}
}

void	draw_square(int x, int y, int size, int color, t_minimap *minimap)
{
	int	i;

	i = 0;
	while (i < size)
	{
		put_pixel_minimap(x + i, y, color, minimap);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel_minimap(x, y + i, color, minimap);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel_minimap(x + size, y + i, color, minimap);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel_minimap(x + i, y + size, color, minimap);
		i++;
	}
}

void	draw_map(t_game *env, t_minimap *minimap)
{
	char	**map;
	int		color;
	int		y;
	int	x;

	y = 0;
	x = 0;
	map = env->map.grid;
	color = 0x0000FF;
	while (map[y])
	{
		x = 0;
		while(map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, color, minimap);
			x++;
		}
		y++;
	}

}

void	init_minimap(t_minimap	*minimap, t_game *env)
{
	minimap->mlx = env->mlx;
	minimap->win = mlx_new_window(env->mlx, 100, 50, "Minimap");
	minimap->img = mlx_new_image(env->mlx, 100, 50);
	minimap->address = mlx_get_data_addr(minimap->img, &minimap->bpp, &minimap->size_line, &minimap->endian);
}

void	build_minimap(t_game *env, t_minimap *minimap)
{
	while (!touch(env->player.x, env->player.y, env))
	{
		put_pixel_minimap((int)env->player.x, (int)env->player.y, 0xFF0000, minimap);
		env->player.x += cos(env->player.angle);
		env->player.y += sin(env->player.angle);
	}
	draw_square(env->player.x, env->player.y, 10, 0x00FF00, minimap);
	draw_map(env, minimap);
}