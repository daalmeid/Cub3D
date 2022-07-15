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

#include "../includes/libc3d.h"

bool	collider(double pos_x, double pos_y, int world_map[24][24], bool *x, bool *y)
{
	double	theta;
	double	v_x;
	double	v_y;
	double	old_dir;
	bool	no_col;

	no_col = true;
	theta = 0.05;
	v_x = 0.2;
	v_y = 0;
	if (world_map[(int)(pos_y + v_y)][(int)(pos_x + v_x)] == 1)
		return (false);
	while (theta < 6.25) //~360 degrees in radians
	{
		old_dir = v_x;
		v_x = v_x * cos(theta) - v_y * sin(theta);
		v_y = old_dir * sin(theta) + v_y * cos(theta);
		if (x && world_map[(int)(pos_y)][(int)(pos_x + v_x)] == 1)
			*x = false;
		if (y && world_map[(int)(pos_y + v_y)][(int)(pos_x)] == 1)
			*y = false;
		if (world_map[(int)(pos_y + v_y)][(int)(pos_x + v_x)] == 1)
			no_col = false;
		// if nothing works might as well stop calculating to save cpu cycles
		if (no_col == false && (!x || *x == false) && (!y || *y == false))
			return (false);
		theta += 0.05;
	}
	return (no_col);
}
