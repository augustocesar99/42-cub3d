/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:23:23 by acesar-m          #+#    #+#             */
/*   Updated: 2025/08/24 18:23:26 by acesar-m         ###   ########.fr       */
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

# define TILE_SIZE 64

typedef struct s_rgb
{
	int r;
	int g;
	int b;
	int value; // armazenar (r << 16 | g << 8 | b)
}	t_rgb;

typedef struct s_texture
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

typedef struct s_map
{
	char	**grid;     // mapa em matriz
	int		width;      // largura do mapa
	int		height;     // altura do mapa
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;       // direção (vetor)
	double	dir_y;
	double	plane_x;    // plano da câmera (para FOV)
	double	plane_y;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;

	t_map		map;
	t_player	player;

	t_texture	no_tex;
	t_texture	so_tex;
	t_texture	we_tex;
	t_texture	ea_tex;

	t_rgb		floor;
	t_rgb		ceiling;
}	t_game;

#endif
