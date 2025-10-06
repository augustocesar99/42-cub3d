#include "../include/cub3d.h"

/* Ensure t_tex fields start null/zeroed before loading. */

void set_tex_zero(t_tex *t)
{
    t->img = NULL;
    t->addr = NULL;
    t->w = 0;
    t->h = 0;
    t->bpp = 0;
    t->line_len = 0;
    t->endian = 0;
}

int load_texture_path(t_game *e, t_tex *t, const char *path)
{
    int w;
    int h;

    if (!path || !*path)
        return (1);
    set_tex_zero(t);
    t->img = mlx_xpm_file_to_image(e->mlx, (char *)path, &w, &h);
    if (!t->img)
        return (1);
    t->addr = (int *)mlx_get_data_addr(t->img, &t->bpp, &t->line_len, &t->endian);
    if (!t->addr)
    {
        mlx_destroy_image(e->mlx, t->img);
        set_tex_zero(t);
        return (1);
    }
    t->w = w;
    t->h = h;
    return (0);
}

void destroy_texture(t_game *e, t_tex *t)
{
    if (t->img)
    {
        mlx_destroy_image(e->mlx, t->img);
        t->img = NULL;
    }
    set_tex_zero(t);
}

void destroy_all_textures(t_game *e)
{
    int i;

    i = 0;
    while (i < 4)
    {
        destroy_texture(e, &e->tex[i]);
        i++;
    }
}

/* Returns non-zero on error; destroys any previously loaded textures */
int load_all_textures(t_game *e,
        const char *no, const char *so, const char *we, const char *ea)
{
    if (load_texture_path(e, &e->tex[TEX_NO], no))
        return (destroy_all_textures(e), 1);
    if (load_texture_path(e, &e->tex[TEX_SO], so))
        return (destroy_all_textures(e), 1);
    if (load_texture_path(e, &e->tex[TEX_WE], we))
        return (destroy_all_textures(e), 1);
    if (load_texture_path(e, &e->tex[TEX_EA], ea))
        return (destroy_all_textures(e), 1);
    return (0);
}

/* Safe texel fetch that respects line_len and bpp; returns packed int color */
int tex_get_pixel(const t_tex *t, int x, int y)
{
    char    *p;

    if (!t || !t->addr)
        return (0);
    if (x < 0 || y < 0 || x >= t->w || y >= t->h)
        return (0);
    p = (char *)t->addr;
    p += y * t->line_len + x * (t->bpp / 8);
    return (*(int *)p);
}
