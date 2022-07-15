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

#include "../includes/libc3d.h"

static void	rotation_handler(t_player *p, double theta)
{
	double	cs;
	double	sn;
	double	old_dir;

	if (theta == 0)
		return ;
	cs = cos(theta);
	sn = sin(theta);
	old_dir = p->dir.x;
	p->dir.x = p->dir.x * cs - p->dir.y * sn;
	p->dir.y = old_dir * sn + p->dir.y * cs;
	old_dir = p->plane.x;
	p->plane.x = p->plane.x * cs - p->plane.y * sn;
	p->plane.y = old_dir * sn + p->plane.y * cs;
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
    if (x < 0 || x > map_width || y > map_height || y < 0 || p->mouse.x == x)
    {
        p->mouse.x = -1;
        p->mouse.y = -1;
        return (0);
    }
    // when mouse going back to window reset latest position
    if (p->mouse.x == -1 || p->mouse.y == -1)
    {
        p->mouse.x = x;
        p->mouse.y = y;
        return (0);
    } 

	if (p->mouse.x - x > 0) // left
	{
		// increase speed relative of to the left edge
		off_x = (double)(map_width - x) / 1024 * accelaration;
		// calculate speed
		mouse_x = -((double)(p->mouse.x - x) * off_x) / 64 * sensivity;
	}
	else if (p->mouse.x - x < 0) // right
	{
		// increase speed relative to the right edge
		off_x = (double)x / 1024 * accelaration;
		// calculate speed
		mouse_x = ((double)-(p->mouse.x - x) * off_x) / 64 * sensivity;
	}
	// allow minimun movement when returning mouse
	reset_x = 0.002 * sensivity * off_x;
	if (x < (map_width / 2.5) && x > p->mouse.x && mouse_x > reset_x)
		mouse_x = reset_x;
	else if (x > (map_width - map_width / 2.5) && x < p->mouse.x && mouse_x < -reset_x)
		mouse_x = -reset_x;
	// limit the maximum speed
	if (mouse_x > 2.0)
		mouse_x = 2.0;
	// save current positon
	p->mouse.x = x;
	return (mouse_x);
}

int	handle_key_events(t_player *p, int world_map[24][24])
{
	double	x = 0.0;
	double	y = 0.0;
	bool	collision;
	
	x = ((p->dir.x * p->wasd[0]) + (p->dir.y * p->wasd[1])
		- (p->dir.x * p->wasd[2]) - (p->dir.y * p->wasd[3])) / 30;
	y = ((p->dir.y * p->wasd[0]) - (p->dir.x * p->wasd[1])
		- (p->dir.y * p->wasd[2]) + (p->dir.x) * p->wasd[3]) / 30;
	rotation_handler(p, handle_mouse(p) + (p->wasd[5] * 0.015165 - p->wasd[4] * 0.015165));
	if (x != 0 || y != 0)
	{
		bool x_ok = true, y_ok = true;
		collision = collider(p->pos.x + x, p->pos.y + y, world_map, &x_ok, &y_ok);
		if (collision == true)
		{
			p->pos.x += x;
			p->pos.y += y;
		}
		else
		{
			collider(p->pos.x + x, p->pos.y, world_map, NULL, NULL);
			if ((x_ok && !y_ok) || collider(p->pos.x + x, p->pos.y, world_map, NULL, NULL))
				p->pos.x += x;
			if ((y_ok && !x_ok) || collider(p->pos.x, p->pos.y + y, world_map, NULL, NULL))
				p->pos.y += y;
		}
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
	mlx_put_image_to_window(p->mlx[0], p->mlx[1], p->map_data.ptr, 0, 0);
	return (0);
}
