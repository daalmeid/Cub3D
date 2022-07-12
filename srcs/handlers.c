/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:36:01 by marvin            #+#    #+#             */
/*   Updated: 2022/06/30 16:36:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Cub3D.h"
#include "../headers/libft.h"

static void	rotation_handler(t_player *p, double theta, int world_map[24][24], bool collision)
{
	double	cs;
	double	sn;
	double	old_dir;

	cs = cos(theta);
	sn = sin(theta);
	old_dir = p->dir_x;
	p->dir_x = p->dir_x * cs - p->dir_y * sn;
	p->dir_y = old_dir * sn + p->dir_y * cs;
	old_dir = p->cam_plane.dir_x;
	p->cam_plane.dir_x = p->cam_plane.dir_x * cs - p->cam_plane.dir_y * sn;
	p->cam_plane.dir_y = old_dir * sn + p->cam_plane.dir_y * cs;
	if ((!p->wasd[0] && !p->wasd[1] && !p->wasd[2] && !p->wasd[3]) || collision == false)
	{
		mlx_destroy_image(p->mlx[0], p->mlx[2]);
		p->mlx[2] = mlx_new_image(p->mlx[0], 800, 400);
		if (!p->mlx[2])
		{
			perror("Error creating image");
			mlx_destroy_window(p->mlx[0], p->mlx[1]);
			exit(0);
		}
		raycaster(p, world_map);
		mlx_put_image_to_window(p->mlx[0], p->mlx[1], p->mlx[2], 0, 0);
	}
}

int	wasd_handler(t_player *p, int world_map[24][24])
{
	double	x = 0.0;
	double	y = 0.0;
	bool	collision;
	
	if ((p->wasd[0] && p->wasd[2]) || (p->wasd[1] && p->wasd[3]))
		return (1);
	if (p->wasd[0])
	{
		x += (p->dir_x / 30);
		y += (p->dir_y / 30);
	}
	if (p->wasd[1])
	{
		x += (p->dir_y / 30);
		y -= (p->dir_x / 30);
	}
	if (p->wasd[2])
	{
		x -= (p->dir_x / 30);
		y -= (p->dir_y / 30);
	}
	if (p->wasd[3])
	{
		x -= (p->dir_y / 30);
		y += (p->dir_x / 30);
	}
	collision = collider(p->pos_x + x, p->pos_y + y, world_map);

	if (p->wasd[5] && !p->wasd[4])
		rotation_handler(p, 0.0075625, world_map, collision);
	else if (p->wasd[4] && !p->wasd[5])
		rotation_handler(p, -0.0075625, world_map, collision);
	if (collision == true)
	{
		p->pos_x += x;
		p->pos_y += y;
		mlx_destroy_image(p->mlx[0], p->mlx[2]);
		p->mlx[2] = mlx_new_image(p->mlx[0], 800, 400);
		if (!p->mlx[2])
		{
			perror("Error creating image");
			mlx_destroy_window(p->mlx[0], p->mlx[1]);
			exit(0);
		}
		raycaster(p, world_map);
		mlx_put_image_to_window(p->mlx[0], p->mlx[1], p->mlx[2], 0, 0);
	}
	else
		printf("collision.\n");
	return (0);
}

int	handlers(t_player *p)
{
	int			world_map[24][24]=
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	if (p->wasd[0] || p->wasd[1] || p->wasd[2] || p->wasd[3])
		wasd_handler(p, world_map);
	if (p->wasd[5] && !p->wasd[4] && !p->wasd[0] && !p->wasd[1] && !p->wasd[2] && !p->wasd[3])
		rotation_handler(p, 0.0075625, world_map, true);
	else if (p->wasd[4] && !p->wasd[5] && !p->wasd[0] && !p->wasd[1] && !p->wasd[2] && !p->wasd[3])
		rotation_handler(p, -0.0075625, world_map, true);
	raycaster(p, world_map);
	return (0);
}
