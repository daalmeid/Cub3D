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

static void	esc_handler(t_player *p)
{
	mlx_destroy_image(p->mlx[0], p->mlx[2]);
	mlx_destroy_window(p->mlx[0], p->mlx[1]);
	exit(0);
}

static void	rotation_handler(t_player *p, double theta, int world_map[24][24])
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
	mlx_destroy_image(p->mlx[0], p->mlx[2]);
	p->mlx[2] = mlx_new_image(p->mlx[0], 800, 400);
	if (!p->mlx[2])
	{
		perror("Error creating image");
		mlx_destroy_window(p->mlx[0], p->mlx[1]);
		exit(0);
	}
	raycaster(*p, world_map);
	mlx_put_image_to_window(p->mlx[0], p->mlx[1], p->mlx[2], 0, 0);
}

static void	w_handler(t_player *p, int world_map[24][24])
{
	if (collider(p->pos_x + p->dir_x / 3, p->pos_y + p->dir_y / 3, world_map)
		== true)
	{
		p->pos_x += (p->dir_x / 3);
		p->pos_y += (p->dir_y / 3);
		mlx_destroy_image(p->mlx[0], p->mlx[2]);
		p->mlx[2] = mlx_new_image(p->mlx[0], 800, 400);
		if (!p->mlx[2])
		{
			perror("Error creating image");
			mlx_destroy_window(p->mlx[0], p->mlx[1]);
			exit(0);
		}
		raycaster(*p, world_map);
		mlx_put_image_to_window(p->mlx[0], p->mlx[1], p->mlx[2], 0, 0);
	}
	else
		printf("collision north.\n");
}

static void	s_handler(t_player *p, int world_map[24][24])
{
	if (collider(p->pos_x - p->dir_x / 3, p->pos_y - p->dir_y / 3, world_map)
		== true)
	{
		p->pos_x -= (p->dir_x / 3);
		p->pos_y -= (p->dir_y / 3);
		mlx_destroy_image(p->mlx[0], p->mlx[2]);
		p->mlx[2] = mlx_new_image(p->mlx[0], 800, 400);
		if (!p->mlx[2])
		{
			perror("Error creating image");
			mlx_destroy_window(p->mlx[0], p->mlx[1]);
			exit(0);
		}
		raycaster(*p, world_map);
		mlx_put_image_to_window(p->mlx[0], p->mlx[1], p->mlx[2], 0, 0);
	}
	else
		printf("collision south.\n");
}

static void	d_handler(t_player *p, int world_map[24][24])
{
	if (collider(p->pos_x - p->dir_y / 3, p->pos_y + p->dir_x / 3, world_map)
		== true)
	{
		p->pos_x -= (p->dir_y / 3);
		p->pos_y += (p->dir_x / 3);
		mlx_destroy_image(p->mlx[0], p->mlx[2]);
		p->mlx[2] = mlx_new_image(p->mlx[0], 800, 400);
		if (!p->mlx[2])
		{
			perror("Error creating image");
			mlx_destroy_window(p->mlx[0], p->mlx[1]);
			exit(0);
		}
		raycaster(*p, world_map);
		mlx_put_image_to_window(p->mlx[0], p->mlx[1], p->mlx[2], 0, 0);
	}
	else
		printf("collision east.\n");
}

static void	a_handler(t_player *p, int world_map[24][24])
{
	if (collider(p->pos_x + p->dir_y / 3, p->pos_y - p->dir_x / 3, world_map)
		== true)
	{
		p->pos_x += (p->dir_y / 3);
		p->pos_y -= (p->dir_x / 3);
		mlx_destroy_image(p->mlx[0], p->mlx[2]);
		p->mlx[2] = mlx_new_image(p->mlx[0], 800, 400);
		if (!p->mlx[2])
		{
			perror("Error creating image");
			mlx_destroy_window(p->mlx[0], p->mlx[1]);
			exit(0);
		}
		raycaster(*p, world_map);
		mlx_put_image_to_window(p->mlx[0], p->mlx[1], p->mlx[2], 0, 0);
	}
	else
		printf("collision west.\n");
}

int	handlers(int key, void *param)
{
	t_player	*p;
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

	p = (t_player *)param;
	if (key == KEY_ESC)
		esc_handler(p);
	else if (key == KEY_W)
		w_handler(p, world_map);
	else if (key == KEY_S)
		s_handler(p, world_map);
	else if (key == KEY_D)
		d_handler(p, world_map);
	else if (key == KEY_A)
		a_handler(p, world_map);
	else if (key == KEY_RGT_ARR)
		rotation_handler(p, 0.075, world_map);
	else if (key == KEY_LFT_ARR)
		rotation_handler(p, -0.075, world_map);
	return (0);
}
