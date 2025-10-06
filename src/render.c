#include "../include/cub3d.h"
#include <math.h>
#include <stdlib.h>

/* ---------- map helpers ------------------------------------------------ */

static int map_wall(t_game *e, int mx, int my)
{
    int     w;
    char    *row;

    if (my < 0 || !e->map.grid || !e->map.grid[my])
        return (1);
    row = e->map.grid[my];
    w = (int)ft_strlen(row);
    if (mx < 0 || mx >= w)
        return (1);
    if (row[mx] == '1')
        return (1);
    return (0);
}

/* ---------- camera build (dir/plane from your angle) ------------------- */

static void make_camera(t_game *e, t_vec *dir, t_vec *plane)
{
    dir->x = cos(e->player.angle);
    dir->y = sin(e->player.angle);
    plane->x = -dir->y * FOV_FACTOR;
    plane->y = dir->x * FOV_FACTOR;
}

/* ---------- per-column ray setup -------------------------------------- */

static void ray_setup(t_game *e, t_ray *r, t_vec v[2], int x)
{
    double  cam_x;
    double  px;
    double  py;

    cam_x = 2.0 * x / (double)WIDTH - 1.0;
    r->dir.x = v[0].x + v[1].x * cam_x;
    r->dir.y = v[0].y + v[1].y * cam_x;
    px = e->player.x / (double)TILE_SIZE;
    py = e->player.y / (double)TILE_SIZE;
    r->mapx = (int)px;
    r->mapy = (int)py;
    r->delta.x = (r->dir.x == 0.0) ? 1e30 : fabs(1.0 / r->dir.x);
    r->delta.y = (r->dir.y == 0.0) ? 1e30 : fabs(1.0 / r->dir.y);
    if (r->dir.x < 0.0)
    { r->step_x = -1; r->side.x = (px - r->mapx) * r->delta.x; }
    else
    { r->step_x = 1; r->side.x = (r->mapx + 1.0 - px) * r->delta.x; }
    if (r->dir.y < 0.0)
    { r->step_y = -1; r->side.y = (py - r->mapy) * r->delta.y; }
    else
    { r->step_y = 1; r->side.y = (r->mapy + 1.0 - py) * r->delta.y; }
    r->hit = 0;
}

/* ---------- step through grid (DDA) ----------------------------------- */

static void ray_dda(t_game *e, t_ray *r)
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

/* ---------- distance & texture choice --------------------------------- */

static void compute_dist(t_game *e, t_ray *r)
{
    double  px;
    double  py;

    px = e->player.x / (double)TILE_SIZE;
    py = e->player.y / (double)TILE_SIZE;
    if (r->side_hit == 0)
        r->dist = (r->mapx - px + (1 - r->step_x) / 2.0) / r->dir.x;
    else
        r->dist = (r->mapy - py + (1 - r->step_y) / 2.0) / r->dir.y;
}

static int pick_tex(t_ray *r)
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

/* ---------- draw helpers ---------------------------------------------- */

static void bg_fill_half(t_game *e, int y0, int y1, int color)
{
    int x;
    int y;

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

static void draw_background(t_game *e)
{
    bg_fill_half(e, 0, HEIGHT / 2, e->ceiling);
    bg_fill_half(e, HEIGHT / 2, HEIGHT, e->floor);
}

static void compute_column_bounds(t_ray *r, t_drawcol *d)
{
    d->line_h = (int)(HEIGHT / r->dist);
    d->start = -d->line_h / 2 + HEIGHT / 2;
    if (d->start < 0)
        d->start = 0;
    d->end = d->line_h / 2 + HEIGHT / 2;
    if (d->end >= HEIGHT)
        d->end = HEIGHT - 1;
}

static double wall_x_coord(t_game *e, t_ray *r)
{
    double  wx;

    if (r->side_hit == 0)
        wx = e->player.y / (double)TILE_SIZE + r->dist * r->dir.y;
    else
        wx = e->player.x / (double)TILE_SIZE + r->dist * r->dir.x;
    return (wx - floor(wx));
}

static void prep_tex_params(t_game *e, t_ray *r, t_drawcol *d, t_tex **tx)
{
    double  wx;

    *tx = &e->tex[pick_tex(r)];
    wx = wall_x_coord(e, r);
    d->tex_x = (int)(wx * (double)(*tx)->w);
    if (r->side_hit == 0 && r->dir.x < 0.0)
        d->tex_x = (*tx)->w - d->tex_x - 1;
    if (r->side_hit == 1 && r->dir.y > 0.0)
        d->tex_x = (*tx)->w - d->tex_x - 1;
    d->step = 1.0 * (*tx)->h / d->line_h;
    d->tex_pos = (d->start - HEIGHT / 2 + d->line_h / 2) * d->step;
}

static void draw_textured_column(t_game *e, int x, t_drawcol *d, t_tex *tx)
{
    int     y;
    int     ty;
    int     color;

    y = d->start;
    while (y <= d->end)
    {
        ty = (int)d->tex_pos;
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

/* ---------- main loop: draw one frame --------------------------------- */

int draw_loop(t_game *e)
{
    int         x;
    t_vec       v[2];
    t_ray       r;
    t_drawcol   d;
    t_tex       *tx;

    move_player(e);
    draw_background(e);
    make_camera(e, &v[0], &v[1]);
    x = 0;
    while (x < WIDTH)
    {
        ray_setup(e, &r, v, x);
        ray_dda(e, &r);
        compute_dist(e, &r);
        compute_column_bounds(&r, &d);
        prep_tex_params(e, &r, &d, &tx);
        draw_textured_column(e, x, &d, tx);
        x++;
    }
    mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
    return (0);
}
