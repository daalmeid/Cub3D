/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 09:42:13 by marvin            #+#    #+#             */
/*   Updated: 2022/06/30 09:42:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libc3d.h"

/*2- Calcultates initial distance of the player to the x and y side considering
the movement vector (necessary to have the total distance to the wall) and
defines the direction of the x and y step.*/
static void	side_dist_calc(t_app *p, t_raycast *rc)
{
	rc->map.x = (int)p->pos.x;
	rc->map.y = (int)p->pos.y;
	if (rc->ray_dir.x < 0)
	{
		rc->step.x = -1;
		rc->side_dist.x = (p->pos.x - rc->map.x) * rc->delta_dist.x;
	}
	else
	{
		rc->step.x = 1;
		rc->side_dist.x = (rc->map.x + 1.0 - p->pos.x) * rc->delta_dist.x;
	}
	if (rc->ray_dir.y < 0)
	{
		rc->step.y = -1;
		rc->side_dist.y = (p->pos.y - rc->map.y) * rc->delta_dist.y;
	}
	else
	{
		rc->step.y = 1;
		rc->side_dist.y = (rc->map.y + 1.0 - p->pos.y) * rc->delta_dist.y;
	}
}

/*1- Calculates delta_x and delta_y, which represent the distance between
two x and y coordinates respectively that the ray will have to traverse
considering the movement vector. It then calls the side distance finder,
the hit finder, the identifier of the x coodinate of texture that was
hit and, finally, the painter.*/
static void	delta_calc(int x, t_app *p)
{
	double			camera_x;
	t_raycast		rc;
	t_tex_rc_info	tex;
	double			perp_wall_dist;

	camera_x = 2 * x / (double)MAP_W - 1;
	rc.ray_dir.x = p->dir.x + p->plane.x * camera_x;
	rc.ray_dir.y = p->dir.y + p->plane.y * camera_x;
	if (rc.ray_dir.x != 0)
		rc.delta_dist.x = fabs(1 / rc.ray_dir.x);
	else
		rc.delta_dist.x = 1e30;
	if (rc.ray_dir.y != 0)
		rc.delta_dist.y = fabs(1 / rc.ray_dir.y);
	else
		rc.delta_dist.y = 1e30;
	side_dist_calc(p, &rc);
	tex.side = hit_find(&rc, p->map.data);
	tex.x = get_tex_x(tex.side, rc, p, &perp_wall_dist);
	ft_drawing((int)(MAP_H / perp_wall_dist), tex, x, p);
}

void	raycaster(t_app *p)
{
	int	x;

	x = 0;
	while (x < MAP_W)
		delta_calc(x++, p);
}
