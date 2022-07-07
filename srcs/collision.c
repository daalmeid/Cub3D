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

#include "../headers/Cub3D.h"
#include "../headers/libft.h"

bool	collider(double pos_x, double pos_y, int world_map[24][24])
{
	double	theta;
	double	v_x;
	double	v_y;
	double	old_dir;

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
		if (world_map[(int)(pos_y + v_y)][(int)(pos_x + v_x)] == 1)
			return (false);
		theta += 0.05;
	}
	return (true);
}
