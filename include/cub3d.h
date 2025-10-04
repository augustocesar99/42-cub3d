/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:23:23 by acesar-m          #+#    #+#             */
/*   Updated: 2025/10/04 17:20:57 by acesar-m         ###   ########.fr       */
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

// Configurações de tela e tiles
# define TILE_SIZE 64
# define WIDTH 1280
# define HEIGHT 720

// Teclas
# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307
# define LEFT 65361
# define RIGHT 65363

// Constantes de movimento
# define PI 3.14159265359
# define SPEED 3
# define ANGLE_SPEED 0.06
# define DIRECTION_FACE 'N'

// Máscaras para parser
# define TEX_NO 0x01
# define TEX_SO 0x02
# define TEX_WE 0x04
# define TEX_EA 0x08
# define COLOR_F 0x10
# define COLOR_C 0x20
# define ALL_ELEMENTS 0x3F

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

// Garbage Collector
typedef struct s_malloc
{
	void				*ptr;
	struct s_malloc		*next;
}	t_malloc;
typedef struct	s_rgb
{
	int r;
	int g;
	int b;
	int value;
}	t_rgb;

typedef struct	s_texture
{
	char	*path;
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_dir
{
	char	c;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_dir;


typedef struct	s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct	s_player
{
	double	x;
	double	y;
	double	angle;
	t_bool	key_up;
	t_bool	key_down;
	t_bool	key_right;
	t_bool	key_left;
	t_bool	key_esc;
	t_bool	left_rotate;
	t_bool	right_rotate;

	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_parse
{
	int		fd;
	int		line_number;
	int		elements_found;
	int		map_started;
}	t_parse;

typedef struct	s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*address;
	int			bpp;
	int			size_line;
	int			endian;
	t_map		map;
	t_player	player;
	t_texture	no_tex;
	t_texture	so_tex;
	t_texture	we_tex;
	t_texture	ea_tex;
	t_rgb		floor;
	t_rgb		ceiling;
	t_parse		parse;
}	t_game;

typedef struct	s_minimap
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*address;
	int			bpp;
	int			size_line;
	int			endian;
}	t_minimap;

// Error
void	ft_error(char *msg);
void	check_file_extension(char *filename);

// Parser
void	parse_scene_file(t_game *game, char *filepath);
int		extract_element(t_game *game, char *line);
void	read_map_line(t_game *game, char *raw_line);
void	validate_map_integrity(t_game *game);

// Garbage Collector
void	*ft_malloc(size_t size);
void	ft_gc_free_all(void);
void	ft_gc_exit(int status);
void	ft_free(void *ptr);
void	ft_free_split(char **split);

// init.c
void	init_game(t_game *game);
void	init_player(t_player *player);
void	clear_image(t_game *game);
int		close_win(t_game *game);

// hooks.c
int		key_release(int keycode, t_game *game);
int		key_press(int keycode, t_game *game);

// draw.c
void	put_pixel(int x, int y, int color, t_game *game);
void	move_player(t_game *game);
int		draw_loop(t_game *game);
char	**get_map(void);
t_bool	touch(float px, float py, t_game *game);

// minimap.c
void	draw_square(int x, int y, int size, int color, t_minimap *minimap);
void	draw_map(t_game *game, t_minimap *minimap);
void	build_minimap(t_game *game, t_minimap *minimap);
void	put_pixel_minimap(int x, int y, int color, t_minimap *env);
void	init_minimap(t_minimap *minimap, t_game *game);

#endif