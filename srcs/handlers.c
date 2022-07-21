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

int	handlers(t_app *p)
{
	handle_key_events(p);
	if (!p->mouse_enable)
		mlx_mouse_show(p->mlx.ptr, p->mlx.win);
	else
		mlx_mouse_hide(p->mlx.ptr, p->mlx.win);
	raycaster(p);
	ft_minimap(p, 1, 1);
	mlx_put_image_to_window(p->mlx.ptr, p->mlx.win, p->mlx.data.ptr, 0, 0);
	return (0);
}

int	esc_handler(t_app *p)
{
	int	i;

	i = 0;
	mlx_mouse_show(p->mlx.ptr, p->mlx.win);
	mlx_loop_end(p->mlx.ptr);
	mlx_destroy_window(p->mlx.ptr, p->mlx.win);
	mlx_destroy_image(p->mlx.ptr, p->mlx.data.ptr);
	while (i < 4)
		mlx_destroy_image(p->mlx.ptr, p->tex[i++].ptr);
	mlx_destroy_display(p->mlx.ptr);
	free(p->mlx.ptr);
	map_clean(p, -1, NULL);
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
