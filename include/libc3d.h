/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:53:15 by daalmeid          #+#    #+#             */
/*   Updated: 2022/07/22 16:29:40 by daalmeid         ###   ########.fr       */
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
# include <errno.h>
# include <limits.h>
# include "../srcs/libmlx/mlx.h"
# include "../srcs/libft/libft.h"

typedef unsigned int	t_uint;
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
	KEY_RGT_ARR = 65363,
	KEY_M = 109
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

enum
{
	PATH_NO,
	PATH_SO,
	PATH_EA,
	PATH_WE
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

/* Modifiiers */
# define X_SEN 0.15
# define X_ROT 0.03215
# define X_VEL 48

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
	t_img	hands;
}			t_mlx;

typedef struct s_map
{
	char	**data;
	size_t	size_x;
	size_t	size_y;
}			t_map;

typedef struct s_app
{
	t_mlx	mlx;
	t_v2d	pos;
	t_v2d	dir;
	t_v2d	plane;
	t_v2i	mouse;
	bool	kmap[6];
	t_img	tex[4];
	t_uint	clr_floor;
	t_uint	clr_ceil;
	t_map	map;
	bool	in_window;
	bool	mouse_enable;
}			t_app;

typedef struct s_raycast
{
	t_v2d	ray_dir;
	t_v2d	delta_dist;
	t_v2i	step;
	t_v2d	side_dist;
	t_v2i	map;
}			t_raycast;

typedef struct s_tex_rc_info
{
	int		side;
	int		x;
	double	step;
	double	pos;
}			t_tex_rc_info;

bool		handle_new_image(t_img *dst, void *mlx);
void		my_pixel_put(t_img *data, int x, int y, int color);
t_uint		*get_img_pixel(t_img *data, int x, int y);

void		raycaster(t_app *p);
int			handlers(t_app *p);
int			esc_handler(t_app *p);
void		collision_behaviour(t_app *p, t_v2d v);

void		ft_minimap(t_app *p, int sign_x, int sign_y);
void		fill_cone(t_v2d player, t_v2d lft_vert, t_v2d rgt_vert, t_app *p);

void		hooks(t_app *p);
void		ft_drawing(int line_height, t_tex_rc_info *tex, int x, t_app *p);
char		hit_find(t_raycast *rc, char **map);
int			get_tex_x(int side, t_raycast rc, t_app *p, double *perp_wall_dist);

void		readmap(t_app *map, char const *file);
void		map_clean(t_app *p, int fd, char const *line);

void		cleaner(t_app *p);

#endif
