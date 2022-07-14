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

static void	rotation_handler(t_player *p, double theta)
{
	double	cs;
	double	sn;
	double	old_dir;

	if (theta == 0)
		return ;
	cs = cos(theta);
	sn = sin(theta);
	old_dir = p->dir_x;
	p->dir_x = p->dir_x * cs - p->dir_y * sn;
	p->dir_y = old_dir * sn + p->dir_y * cs;
	old_dir = p->cam_plane.dir_x;
	p->cam_plane.dir_x = p->cam_plane.dir_x * cs - p->cam_plane.dir_y * sn;
	p->cam_plane.dir_y = old_dir * sn + p->cam_plane.dir_y * cs;
}

static double handle_mouse(t_player *p)
{
	// CONST VALUES
	const double sensivity = 1.0;
	const double accelaration = 1.5;

	int x, y;
	double off_x = 1.0;
	double mouse_x = 0.0;
	double reset_x = 0.0;

	mlx_mouse_get_pos(p->mlx[0], p->mlx[1], &x, &y);
	(void)y;

	// ignore mouse movement outside of window
    if (x < 0 || x > map_width || y > map_height || y < 0 || p->mouse_x == x)
    {
        p->mouse_x = -1;
        p->mouse_y = -1;
        return (0);
    }
    // when mouse going back to window reset latest position
    if (p->mouse_x == -1 || p->mouse_y == -1)
    {
        p->mouse_x = x;
        p->mouse_y = y;
        return (0);
    } 

	if (p->mouse_x - x > 0) // left
	{
		// increase speed relative of to the left edge
		off_x = (double)(map_width - x) / 1024 * accelaration;
		// calculate speed
		mouse_x = -((double)(p->mouse_x - x) * off_x) / 64 * sensivity;
	}
	else if (p->mouse_x - x < 0) // right
	{
		// increase speed relative to the right edge
		off_x = (double)x / 1024 * accelaration;
		// calculate speed
		mouse_x = ((double)-(p->mouse_x - x) * off_x) / 64 * sensivity;
	}
	// allow minimun movement when returning mouse
	reset_x = 0.002 * sensivity * off_x;
	if (x < (map_width / 2.5) && x > p->mouse_x && mouse_x > reset_x)
		mouse_x = reset_x;
	else if (x > (map_width - map_width / 2.5) && x < p->mouse_x && mouse_x < -reset_x)
		mouse_x = -reset_x;
	// limit the maximum speed
	if (mouse_x > 2.0)
		mouse_x = 2.0;
	// save current positon
	p->mouse_x = x;
	return (mouse_x);
}

int	handle_key_events(t_player *p, int world_map[24][24])
{
	double	x = 0.0;
	double	y = 0.0;
	bool	collision;
	
	x = ((p->dir_x * p->wasd[0]) + (p->dir_y * p->wasd[1])
		- (p->dir_x * p->wasd[2]) - (p->dir_y * p->wasd[3])) / 30;
	y = ((p->dir_y * p->wasd[0]) - (p->dir_x * p->wasd[1])
		- (p->dir_y * p->wasd[2]) + (p->dir_x) * p->wasd[3]) / 30;
	rotation_handler(p, handle_mouse(p) + (p->wasd[5] * 0.015165 - p->wasd[4] * 0.015165));
	if (x != 0 || y != 0)
	{
		collision = collider(p->pos_x + x, p->pos_y + y, world_map);
		if (collision == true)
		{
			p->pos_x += x;
			p->pos_y += y;
		}
		else
			printf("collision.\n");
	}
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

	handle_key_events(p, world_map);	
	raycaster(p, world_map);
	ft_minimap(p, world_map, 1, 1);
	mlx_put_image_to_window(p->mlx[0], p->mlx[1], p->mlx[2], 0, 0);
	return (0);
}
