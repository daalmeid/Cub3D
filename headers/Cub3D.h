/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:53:15 by daalmeid          #+#    #+#             */
/*   Updated: 2022/07/13 11:29:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx_linux/mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <stdbool.h>

#define map_width 800
#define map_height 400

typedef struct s_data
{
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_camPlane
{
	double	dir_x;
	double	dir_y;
} t_camPlane;

typedef struct s_player
{
	void		*mlx[7];
	bool		wasd[6];
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;

	t_camPlane	cam_plane;

	t_data		tex_data[4];
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
	MlX_TEX_NO = 3,
	MlX_TEX_SO = 4,
	MlX_TEX_WE = 5,
	MlX_TEX_EA = 6
} t_mlx;

t_data	handle_new_image(void *mlx_image);
void	my_pixel_put(t_data *data, int x, int y, int color);
unsigned int	*get_img_pixel(t_data *data, int x, int y);
void	raycaster(t_player *p, int worldMap[24][24]);
int		handlers(t_player *p);
bool	collider(double pos_x, double pos_y, int worldMap[24][24]);

#endif