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

#include "../include/libc3d.h"

static void	rotation_handler(t_app *p, double theta)
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

static double handle_mouse(t_app *p)
{
	// CONST VALUES
	const double sensivity = 1.0;
	const double accelaration = 1.5;

	int x, y;
	double off_x = 1.0;
	double mouse_x = 0.0;
	double reset_x = 0.0;

	mlx_mouse_get_pos(p->mlx.ptr, p->mlx.win, &x, &y);
	if (x < 0 || x > MAP_W || y > MAP_H || y < 0 || p->mouse.x == x)
	{
		p->mouse.x = -1;
		p->mouse.y = -1;
		return (0);
	}
	if (p->mouse.x == -1 || p->mouse.y == -1)
	{
		p->mouse.x = x;
		p->mouse.y = y;
		return (0);
	}
	if (p->mouse.x - x > 0)
	{
		off_x = (double)(MAP_W - x) / 1024 * accelaration;
		mouse_x = -((double)(p->mouse.x - x) * off_x) / 64 * sensivity;
	}
	else if (p->mouse.x - x < 0)
	{
		off_x = (double)x / 1024 * accelaration;
		mouse_x = ((double)-(p->mouse.x - x) * off_x) / 64 * sensivity;
	}
	reset_x = 0.01 * sensivity * off_x;
	if (x < (MAP_W / 2.5) && x > p->mouse.x && mouse_x > reset_x)
		mouse_x = reset_x;
	else if (x > (MAP_W - MAP_W / 2.5) && x < p->mouse.x && mouse_x < -reset_x)
		mouse_x = -reset_x;
	if (mouse_x > 1.0)
		mouse_x = 1.0;
	else if (mouse_x < -1.0)
		mouse_x = -1.0;
	p->mouse.x = x;
	return (mouse_x);
}

int	handle_key_events(t_app *p, int map[24][24])
{
	t_v2d	v;
	t_v2i	r;

	v.x = ((p->dir.x * p->kmap[_W]) + (p->dir.y * p->kmap[_A])
		- (p->dir.x * p->kmap[_S]) - (p->dir.y * p->kmap[_D])) / 30;
	v.y = ((p->dir.y * p->kmap[_W]) - (p->dir.x * p->kmap[_A])
		- (p->dir.y * p->kmap[_S]) + (p->dir.x) * p->kmap[_D]) / 30;
	rotation_handler(p, handle_mouse(p) + (p->kmap[_RA] * 0.015165 - p->kmap[_LA] * 0.015165));
	if (v.x != 0 || v.y != 0)
	{
		r.x = true;
		r.y = true;
		if (collider(p->pos.x + v.x, p->pos.y + v.y, &r, map))
		{
			p->pos.x += v.x;
			p->pos.y += v.y;
		}
		else
		{
			if ((r.x && !r.y) || collider(p->pos.x + v.x, p->pos.y, NULL, map))
				p->pos.x += v.x;
			if ((!r.x && r.y) || collider(p->pos.x, p->pos.y + v.y, NULL, map))
				p->pos.y += v.y;
		}
	}
	return (0);
}

int	handlers(t_app *p)
{
	int map[24][24] = {
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

	handle_key_events(p, map);
	raycaster(p, map);
	ft_minimap(p, map, 1, 1);
	mlx_put_image_to_window(p->mlx.ptr, p->mlx.win, p->mlx.data.ptr, 0, 0);
	return (0);
}
