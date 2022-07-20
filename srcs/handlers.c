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
/*
static double	mouse_moves(t_v2i m_pos, t_app *p, double off_x, double mouse_x)
{
	double	reset_x;

	if (p->mouse.x - m_pos.x > 0)
	{
		off_x = (double)(MAP_W - m_pos.x) / 1024 * ACCELERATION;
		mouse_x = -((double)(p->mouse.x - m_pos.x) * off_x) / 64 * SENSITIVITY;
	}
	else if (p->mouse.x - m_pos.x < 0)
	{
		off_x = (double)(m_pos.x) / 1024 * ACCELERATION;
		mouse_x = ((double)-(p->mouse.x - m_pos.x) * off_x) / 64 * SENSITIVITY;
	}
	reset_x = 0.01 * SENSITIVITY * off_x;
	if (m_pos.x < (MAP_W / 2.5) && m_pos.x > p->mouse.x && mouse_x > reset_x)
		mouse_x = reset_x;
	else if (m_pos.x > (MAP_W - MAP_W / 2.5) && m_pos.x < p->mouse.x
		&& mouse_x < -reset_x)
		mouse_x = -reset_x;
	if (mouse_x > 1.0)
		mouse_x = 1.0;
	else if (mouse_x < -1.0)
		mouse_x = -1.0;
	p->mouse.x = m_pos.x;
	return (mouse_x);
}

static double	handle_mouse(t_app *p)
{
	t_v2i			m_pos;

	mlx_mouse_get_pos(p->mlx.ptr, p->mlx.win, &(m_pos.x), &(m_pos.y));
	//mlx_mouse_move(p->mlx.ptr, p->mlx.win, MAP_W / 2, MAP_H / 2);
	if (m_pos.x < 0 || m_pos.x > MAP_W || m_pos.y > MAP_H
		|| m_pos.y < 0 || p->mouse.x == m_pos.x)
	{
		p->mouse.x = -1;
		p->mouse.y = -1;
		return (0);
	}
	if (p->mouse.x == -1 || p->mouse.y == -1)
	{
		p->mouse.x = m_pos.x;
		p->mouse.y = m_pos.y;
		return (0);
	}
	return (mouse_moves(m_pos, p, 1.0, 0.0));
}
*/

static double	handle_mouse(t_app *p)
{
	t_v2i			m_pos;
	double			mouse_x;

	(void)p;
	mouse_x = 0.0;
	mlx_mouse_get_pos(p->mlx.ptr, p->mlx.win, &(m_pos.x), &(m_pos.y));
	if (m_pos.x != MAP_W / 2 || m_pos.y != MAP_H / 2)
	{
		if (m_pos.x < MAP_W / 2 - 1)
		{
			//off_x = (double)(MAP_W - m_pos.x) / 1024 * ACCELERATION;
			mouse_x = -((double)(MAP_W / 2 - m_pos.x) /** off_x*/) / 64 * X_SEN;
		}
		else if (m_pos.x > MAP_W / 2 + 1)
		{
			//off_x = (double)(m_pos.x) / 1024 * ACCELERATION;
			mouse_x = ((double)-(MAP_W / 2 - m_pos.x) /** off_x*/) / 64 * X_SEN;
		}
		//printf("x: %d y: %d\n", m_pos.x, m_pos.y);
		mlx_mouse_move(p->mlx.ptr, p->mlx.win, MAP_W / 2, MAP_H / 2);
	}
	return (mouse_x);
}

int	handle_key_events(t_app *p)
{
	t_v2d	v;

	v.x = ((p->dir.x * p->kmap[_W]) + (p->dir.y * p->kmap[_A])
			- (p->dir.x * p->kmap[_S]) - (p->dir.y * p->kmap[_D])) / X_VEL;
	v.y = ((p->dir.y * p->kmap[_W]) - (p->dir.x * p->kmap[_A])
			- (p->dir.y * p->kmap[_S]) + (p->dir.x) * p->kmap[_D]) / X_VEL;
	rotation_handler(p,
		(handle_mouse(p) + (p->kmap[_RA] * X_ROT - p->kmap[_LA] * X_ROT)) / 2);
	if (v.x != 0 || v.y != 0)
		collision_behaviour(p, v);
	return (0);
}

int	handlers(t_app *p)
{
	if (p->stat == true)
	{
		mlx_clear_window(p->mlx.ptr, p->mlx.win);
		mlx_string_put(p->mlx.ptr, p->mlx.win, MAP_W / 2 - 5, MAP_H / 2, 0xffffff, "paused");
		return (0);
	}
	handle_key_events(p);
	raycaster(p);
	ft_minimap(p, 1, 1);
	mlx_put_image_to_window(p->mlx.ptr, p->mlx.win, p->mlx.data.ptr, 0, 0);
	return (0);
}
