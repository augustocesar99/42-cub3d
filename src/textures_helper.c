#include "../include/cub3d.h"

int	tex_get_pixel(const t_texture *t, int x, int y)
{
	char	*p;

	if (!t || !t->addr)
		return (0);
	if (x < 0 || y < 0 || x >= t->w || y >= t->h)
		return (0);
	p = (char *)t->addr;
	p += y * t->line_len + x * (t->bpp / 8);
	return (*(int *)p);
}

void	destroy_texture(t_game *e, t_texture *t)
{
	if (t->img)
	{
		mlx_destroy_image(e->mlx, t->img);
		t->img = NULL;
	}
	set_tex_zero(t);
}

void	destroy_all_textures(t_game *e)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		destroy_texture(e, &e->tex[i]);
		i++;
	}
}

void	set_tex_zero(t_texture *t)
{
	t->img = NULL;
	t->addr = NULL;
	t->w = 0;
	t->h = 0;
	t->bpp = 0;
	t->line_len = 0;
	t->endian = 0;
}
