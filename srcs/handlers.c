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

static void		rotation_handler(t_app *p, double theta);
static double	handle_mouse(t_app *p);
static int		handle_key_events(t_app *p);
static void		draw_hands(t_app *p);

int	handlers(t_app *p)
{
	handle_key_events(p);
	if (!p->mouse_enable)
		mlx_mouse_show(p->mlx.ptr, p->mlx.win);
	else
		mlx_mouse_hide(p->mlx.ptr, p->mlx.win);
	raycaster(p);
	draw_hands(p);
	ft_minimap(p, 1, 1);
	mlx_put_image_to_window(p->mlx.ptr, p->mlx.win, p->mlx.data.ptr, 0, 0);
	return (0);
}

static void	draw_hands(t_app *p)
{
	t_v2d	pos;
	t_v2i	put;
	t_v2d	incr;
	t_uint	color;

	pos.y = p->mlx.hands.height;
	put.y = MAP_H;
	incr.x = fabs((double)p->mlx.hands.width / (MAP_W / 3));
	incr.y = fabs((double)p->mlx.hands.height / (MAP_H / 3));
	while (pos.y >= 0)
	{
		pos.x = 0;
		put.x = MAP_W / 3;
		while (pos.x < p->mlx.hands.width)
		{
			color = *get_img_pixel(&p->mlx.hands, (int)(pos.x), (int)(pos.y));
			if (color != 0xff000000)
				my_pixel_put(&p->mlx.data, put.x, put.y, color);
			pos.x += incr.x;
			put.x += 1;
		}
		pos.y -= incr.y;
		put.y -= 1;
	}
}

int	esc_handler(t_app *p)
{
	mlx_mouse_show(p->mlx.ptr, p->mlx.win);
	mlx_loop_end(p->mlx.ptr);
	cleaner(p);
	exit(0);
	return (0);
}

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

static double	handle_mouse(t_app *p)
{
	t_v2i			m_pos;
	double			mouse_x;

	if (!p->mouse_enable || !p->in_window)
		return (0);
	mouse_x = 0.0;
	mlx_mouse_get_pos(p->mlx.ptr, p->mlx.win, &(m_pos.x), &(m_pos.y));
	if (m_pos.x >= 0 && m_pos.x <= MAP_W && m_pos.y >= 0 && m_pos.y <= MAP_H
		&& (m_pos.x != MAP_W / 2 || m_pos.y != MAP_H / 2))
	{
		if (m_pos.x < MAP_W / 2 - 1)
			mouse_x = -((double)(MAP_W / 2 - m_pos.x) / 64) * X_SEN;
		else if (m_pos.x > MAP_W / 2 + 1)
			mouse_x = ((double)-(MAP_W / 2 - m_pos.x) / 64) * X_SEN;
		mlx_mouse_move(p->mlx.ptr, p->mlx.win, MAP_W / 2, MAP_H / 2);
	}
	return (mouse_x);
}

static int	handle_key_events(t_app *p)
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
