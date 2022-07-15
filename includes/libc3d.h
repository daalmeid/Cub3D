/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:53:15 by daalmeid          #+#    #+#             */
/*   Updated: 2022/07/15 21:02:44 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBC3D_H
# define LIBC3D_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <stdbool.h>
# include "../mlx_linux/mlx.h"
# include "libft.h"

typedef unsigned int uint;
# define MAP_W 800
# define MAP_H 400

/* MAP KEYS */
enum
{
	KEY_ESC = 65307,
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_LFT_ARR = 65361,
	KEY_RGT_ARR = 65363
};
enum
{
	_W = 0,
	_A = 1,
	_S = 2,
	_D = 3,
	_LA = 4,
	_RA = 5
};

/* Minimap colors */
enum
{
	CLR_B = 0xadd8e6,
	CLR_P = 0x111111,
	CLR_W = 0x3f301d,
	CLR_F = 0x98ee90,
	CLR_L = 0xffffff,
	CLR_D = 0x000000,
};

typedef struct s_v2i
{
	int	x;
	int	y;
}		t_v2i;

typedef struct s_v2d
{
	double	x;
	double	y;
}			t_v2d;

typedef struct s_img
{
	void	*ptr;
	void	*addr;
	char	*path;
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
}			t_img;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	t_img	data;
}		t_mlx;

typedef struct s_app
{
	t_mlx	mlx;
	t_v2d	pos;
	t_v2d	dir;
	t_v2i	mouse;
	t_v2d	plane;
	bool	kmap[6];
	t_img	tex[4];
} t_app;

typedef struct s_raycast
{
	t_v2d	ray_dir;
	t_v2d	delta_dist;
	t_v2i	step;
	t_v2d	side_dist;
	t_v2i	map;
} t_raycast;

bool		handle_new_image(t_img *dst, void *mlx);
void		my_pixel_put(t_img *data, int x, int y, int color);
uint		*get_img_pixel(t_img *data, int x, int y);
void		raycaster(t_app *p, int map[24][24]);
int			handlers(t_app *p);
bool		collider(double pos_x, double pos_y, t_v2i *r, int map[24][24]);
void		ft_minimap(t_app *p, int map[24][24], int sign_x, int sign_y);
int			ft_line_creation(int x, int y, t_app *p);

#endif
