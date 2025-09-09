/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller- <ekeller-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:23:23 by acesar-m          #+#    #+#             */
/*   Updated: 2025/09/09 16:21:03 by ekeller-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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

# define TILE_SIZE 64
# define	WIDTH 1200
# define	HEIGHT 800
//keyhooks
# define	W 119
# define	A 97
# define	S 115
# define	D 100
# define	pi 3.14159265359
# define	ESC 65307

typedef struct	s_malloc
{
	void				*ptr;
	struct s_malloc		*next;
}	t_malloc;

typedef struct	s_rgb
{
	int r;
	int g;
	int b;
	int value; // armazenar (r << 16 | g << 8 | b)
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
	bool	key_up;
	bool	key_down;
	bool	key_right;
	bool	key_left;
	bool	key_esc;
	
	double	dir_x;       // direção (vetor)
	double	dir_y;
	double	plane_x;    // plano da câmera (para FOV)
	double	plane_y;
}	t_player;

typedef struct s_parse
{
	int		fd;
	int		line_number;
	int		elements_found; // bitmask para verificar elementos
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
	// t_texture	no_tex;
	// t_texture	so_tex;
	// t_texture	we_tex;
	// t_texture	ea_tex;
	// t_rgb		floor;
	// t_rgb		ceiling;
	// t_parse		parse;
}	t_game;

// Garbage Collector
void	*ft_malloc(size_t size);
void	ft_gc_free_all(void);
void	ft_gc_exit(int status);
void	ft_free(void *ptr);

//init.c
void	init_game(t_game *env);
void	init_player(t_player *player);
void    move_player(t_player *player);
int 	key_release(int keycode, t_game *env);
int 	key_press(int keycode, t_game *env);



#endif
