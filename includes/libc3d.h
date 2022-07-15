/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:53:15 by daalmeid          #+#    #+#             */
/*   Updated: 2022/07/15 15:35:31 by rafernan         ###   ########.fr       */
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

#define map_width 800
#define map_height 400

typedef struct s_img
{
	void	*ptr;
	void	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
}			t_img;

typedef struct s_v2i
{
	int	x;
	int	y;
}	t_v2i;

typedef struct s_v2d
{
	double	x;
	double	y;
}	t_v2d;

typedef struct s_player
{
	void	*mlx[2];
	bool	wasd[6];
	t_v2d	pos;
	t_v2d	dir;
	t_v2i	mouse;
	t_v2d	plane;

	t_img		tex[4];
	t_img		map_data;
} t_player;

typedef struct s_raycast
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	int		map_x;
	int		map_y;
} t_raycast;

typedef enum	e_keys
{
	KEY_A = 97,
	KEY_D = 100,
	KEY_S = 115,
	KEY_W = 119,
	KEY_ESC = 65307,
	KEY_LFT_ARR = 65361,
	KEY_RGT_ARR = 65363
} t_keys;

typedef enum	e_mlx
{
	MLX_INIT = 0,
	MLX_WINDOW = 1,
	MLX_IMG_MAIN = 2,
	/*
	MlX_TEX_NO = 3,
	MlX_TEX_SO = 4,
	MlX_TEX_WE = 5,
	MlX_TEX_EA = 6
	*/
} t_mlx;


bool	handle_new_image(t_img *dst, void *mlx, char const *path);
void	my_pixel_put(t_img *data, int x, int y, int color);
unsigned int	*get_img_pixel(t_img *data, int x, int y);
void	raycaster(t_player *p, int worldMap[24][24]);
int		handlers(t_player *p);
bool	collider(double pos_x, double pos_y, int worldMap[24][24], bool *x, bool *y);
void	ft_minimap(t_player *p, int world_map[24][24], int sign_x, int sign_y);
int		ft_line_creation(int x, int y, t_player *p);

#endif
