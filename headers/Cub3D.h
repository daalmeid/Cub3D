/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:53:15 by daalmeid          #+#    #+#             */
/*   Updated: 2022/07/06 12:50:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../mlx_linux/mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <stdbool.h>

#define mapWidth 800
#define mapHeightPix 400

typedef struct s_data
{
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_camPlane
{
	double	dirX;
	double	dirY;
} t_camPlane;

typedef struct s_player
{
	void	*mlx[3];
	
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;

	t_camPlane	camPlane;
} t_player;


t_data	handle_new_image(void **mlx);
void	my_pixel_put(t_data *data, int x, int y, int color);
void	raycaster(t_player p, int worldMap[24][24]);
int		handlers(int key, void *param);
bool	collider(double posX, double posY, int worldMap[24][24]);

#endif