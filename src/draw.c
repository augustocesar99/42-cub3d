#include "../include/cub3d.h"

void    put_pixel(int x, int y, int color, t_game *env)
{

    char	*pxl;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pxl = env->address +(y * env->size_line
				+ x * (env->bpp / 8));
		*(unsigned int *)pxl = color;
	}
}

void    draw_square(int x, int y, int size, int color, t_game * env)
{
    int i;

    i = 0;
    while (i < size)
    {
        put_pixel(x + i, y, color, env);
        i++;
    }
    i = 0;
    while (i < size)
    {
        put_pixel(x, y + i, color, env);
        i++;
    }
    i = 0;
    while (i < size)
    {
        put_pixel(x + size, y + i, color, env);
        i++;
    }
    i = 0;
    while (i < size)
    {
        put_pixel(x + i, y + size, color, env);
        i++;
    }
}

void    move_player(t_game *env)
{
    double  cos_angle;
    double  sin_angle;
	float	old_x;
	float	old_y;

	old_x = env->player.x;
	old_y = env->player.y;
    if (env->player.left_rotate)
        env->player.angle -= ANGLE_SPEED;
    if (env->player.right_rotate)
        env->player.angle += ANGLE_SPEED;
    if (env->player.angle > 2 * PI)
        env->player.angle = 0;
    if (env->player.angle < 0)
        env->player.angle = 2 * PI;
    
	cos_angle = cos(env->player.angle);
    sin_angle = sin(env->player.angle);
    
    if (env->player.key_up)
    {
        env->player.x += cos_angle * SPEED;
        env->player.y -= sin_angle * SPEED;
    }
    if (env->player.key_down)
    {
        env->player.x -= cos_angle * SPEED;
        env->player.y += sin_angle * SPEED;
    }
    if (env->player.key_left)
    {
        env->player.x -= sin_angle * SPEED;
        env->player.y -= cos_angle * SPEED;
    }
    if (env->player.key_right)
    {
        env->player.x += sin_angle * SPEED;
        env->player.y += cos_angle * SPEED;
    }
	if (touch(env->player.x, env->player.y, env))
    {
        env->player.x = old_x;
        env->player.y = old_y;
    }

}

void    draw_map(t_game * env)
{
    char    **map;
    int     color;
    int     y;
    int     x;

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
                draw_square(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, color, env);
            x++;
        }
        y++;
    }

}
bool    touch(float px, float py, t_game *env)
{
    int x;
    int y;
	int	rows;

	rows = 0;
    x = px / TILE_SIZE;
    y = py / TILE_SIZE;
	if (y < 0 || x < 0)
		return (true);
	while (env->map.grid[rows])
		rows++;
	if (y >= rows)
		return (true);
	if (env->map.grid[y] == NULL)
		return (true);
	if (x > (int) ft_strlen(env->map.grid[y]))
		return (true);
    if (env->map.grid[y][x] == '1')
        return (true);
    return (false);
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

void draw_line(t_game *env, float start_x, int i)
{
	float	ray_x;
	float	ray_y;

	
	ray_x = env->player.x;
	ray_y = env->player.y;
	while (!touch(ray_x, ray_y, env))
	{
		//put_pixel((int)ray_x, (int)ray_y, 0xFF0000, env);
		ray_x += cos(start_x);
		ray_y += sin(start_x);
	}
	float	dist = distance(ray_x - env->player.x, ray_y - env->player.y);
	float	height = (TILE_SIZE / dist) * WIDTH / 2;
	int		start_y = (HEIGHT - height) / 2;
	int		end = start_y + height;
	while(start_y < end)
	{
		put_pixel(i, start_y, 255, env);
		start_y++;
	}

}

int draw_loop(t_game *env)
{
    float       ray_x;
    float       ray_y;
	float		fraction;
	float		start_x;
	int			i;

    fraction = PI / 3 / WIDTH;
	start_x = env->player.angle - PI / 6;
	i = 0;
	move_player(env);
    clear_image(env);
    ray_x = env->player.x;
    ray_y = env->player.y;
	while (!touch(ray_x, ray_y, env))
	{
		//put_pixel((int)ray_x, (int)ray_y, 0xFF0000, env);
		ray_x += cos(env->player.angle);
		ray_y += sin(env->player.angle);
	}
    //draw_square(env->player.x, env->player.y, 10, 0x00FF00, env);
    //draw_map(env);
	while (i < WIDTH)
	{
		draw_line(env, start_x, i);
		start_x += fraction;
		i++;
	}
		


    mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
    return (0);

}

char    **get_map(void)
{
    char    **map;

    map = ft_malloc(sizeof(char *)  * 10);
    map[0] = "1111111111111";
    map[1] = "1010000000001";
    map[2] = "1010000000001";
    map[3] = "1000010000001";
    map[4] = "1000000000001";
    map[5] = "1000000000001";
    map[6] = "1000100000001";
    map[7] = "1000000000001";
    map[8] = "1111111111111";
    map[9] = NULL;
    return (map);
}