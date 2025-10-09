#include "../include/cub3d.h"

int	map_wall(t_game *e, int mx, int my)
{
	int		w;
	char	*row;

	if (my < 0 || !e->map.grid || !e->map.grid[my])
		return (1);
	row = e->map.grid[my];
	w = ft_strlen(row);
	if (mx < 0 || mx >= w)
		return (1);
	if (row[mx] == '1')
		return (1);
	return (0);
}

void	bg_fill_half(t_game *e, int y0, int y1, int color)
{
	int	x;
	int	y;

	y = y0;
	while (y < y1)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, color, e);
			x++;
		}
		y++;
	}
}

void	draw_background(t_game *e)
{
	bg_fill_half(e, 0, HEIGHT / 2, e->ceiling.value);
	bg_fill_half(e, HEIGHT / 2, HEIGHT, e->floor.value);
}
