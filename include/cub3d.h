/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:23:23 by acesar-m          #+#    #+#             */
/*   Updated: 2025/10/07 17:01:26 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include <stdbool.h>

//64
# define	TILE_SIZE 64
# define	WIDTH 1280
# define	HEIGHT 720
# define	FOV_FACTOR 0.66
//keyhooks
# define	W 119
# define	A 97
# define	S 115
# define	D 100
# define	PI 3.14159265359
# define	ESC 65307
# define	LEFT 65361
# define	RIGHT 65363

# define	SPEED 1.5
# define	ANGLE_SPEED 0.03

typedef struct	s_malloc
{
	void				*ptr;
	struct s_malloc		*next;
}	t_malloc;

// typedef struct	s_rgb
// {
// 	int r;
// 	int g;
// 	int b;
// 	int value; // armazenar (r << 16 | g << 8 | b)
// }	t_rgb;


typedef struct	s_texture
{
	char	*path;
	void	*img;
	char	*addr;
	int		w;
	int		h;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct	s_map
{
	char	**grid;     // mapa em matriz
	int		width;      // largura do mapa
	int		height;     // altura do mapa
}	t_map;

typedef struct	s_player
{
	double	x;
	double	y;
	double	angle;
	bool	key_up;
	bool	key_down;
	bool	key_right;
	bool	key_left;
	bool	key_esc;
	bool	left_rotate;
	bool	right_rotate;

	// double	dir_x;       // direção (vetor)
	// double	dir_y;
	// double	plane_x;    // plano da câmera (para FOV)
	// double	plane_y;
}	t_player;

typedef struct	s_parse
{
	int		fd;
	int		line_number;
	int		elements_found; // bitmask para verificar elementos
	int		map_started;
}	t_parse;

typedef struct	s_game
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*address;
	int				bpp;
	int				size_line;
	int				endian;
	t_map			map;
	t_player		player;
	t_texture		tex[4];
	unsigned int	floor;
	unsigned int	ceiling;
	t_parse			parse;
	t_texture		no_tex;
	t_texture		so_tex;
	t_texture		we_tex;
	t_texture		ea_tex;
}	t_game;

//Struct additions:
typedef enum	e_texid
{
	TEX_NO = 0,
	TEX_SO = 1,
	TEX_WE = 2,
	TEX_EA = 3
}	t_texid;

typedef struct	s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct	s_ray
{
	t_vec	dir;        /* rayDirX/rayDirY */
	int		mapx;
	int		mapy;
	t_vec	delta;      /* deltaDistX/Y */
	t_vec	side;       /* sideDistX/Y */
	int		step_x;
	int		step_y;
	int		hit;        /* 0 -> keep DDA; 1 -> wall hit */
	int		side_hit;   /* 0 -> X-side; 1 -> Y-side */
	double	dist;       /* perpWallDist */
}	t_ray;

typedef struct	s_drawcol
{
	int		line_h;
	int		start;
	int		end;
	double	step;
	double	tex_pos;
	int		tex_x;
}	t_drawcol;

//End struct additions

// Garbage Collector
void	*ft_malloc(size_t size);
void	ft_gc_free_all(void);
void	ft_gc_exit(int status);
void	ft_free(void *ptr);

//init.c
void	init_game(t_game *env);
void	init_player(t_player *player);
void	clear_image(t_game * env);
int		close_win(t_game *env);


//hooks.c
int		key_release(int keycode, t_game *env);
int		key_press(int keycode, t_game *env);

//draw.c
void	put_pixel(int x, int y, int color, t_game *env);
void	move_player(t_game *env);
char	**get_map(void);
bool	touch(float px, float py, t_game *env);

//render.c
int		map_wall(t_game *e, int mx, int my);
int		draw_loop(t_game *env);

/* textures API */
int		load_texture_path(t_game *e, t_texture *t, const char *path);
int		load_all_textures(t_game *e);
void	destroy_texture(t_game *e, t_texture *t);
void	destroy_all_textures(t_game *e);
int		tex_get_pixel(const t_texture *t, int x, int y);
void	set_tex_zero(t_texture *t);

#endif