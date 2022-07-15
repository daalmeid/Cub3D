/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 12:00:34 by marvin            #+#    #+#             */
/*   Updated: 2022/07/01 12:00:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libc3d.h"

bool	collider(double pos_x, double pos_y, t_v2i *r, int map[24][24])
{
	t_v2d	v;
	double	old_dir;
	bool	no_col;
	double	theta;

	no_col = true;
	theta = 0.05;
	v.x = 0.2;
	v.y = 0;
	while (theta < 6.25) //~360 degrees in radians
	{
		old_dir = v.x;
		v.x = v.x * cos(theta) - v.y * sin(theta);
		v.y = old_dir * sin(theta) + v.y * cos(theta);
		if (r && map[(int)(pos_y)][(int)(pos_x + v.x)] == 1)
			r->x = false;
		if (r && map[(int)(pos_y + v.y)][(int)(pos_x)] == 1)
			r->y = false;
		if (map[(int)(pos_y + v.y)][(int)(pos_x + v.x)] == 1)
			no_col = false;
		// if nothing works might as well stop calculating to save cpu cycles
		if (no_col == false && (!r || r->x == false) && (!r || r->y == false))
			return (false);
		theta += 0.01;
	}
	return (no_col);
}
