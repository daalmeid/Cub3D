/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_hit_find.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:08:39 by marvin            #+#    #+#             */
/*   Updated: 2022/07/18 17:08:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libc3d.h"

/*5-Find the x-coordinate of the texture corresponding to the hit*/
int	get_tex_x(char side, t_raycast rc, t_app *p, double *perp_wall_dist)
{
	double	wall_x; //where exactly the wall was hit
	int		tex_x;

	if (side == 'W' || side == 'E')
	{
		*perp_wall_dist = rc.side_dist.x - rc.delta_dist.x;
		wall_x = p->pos.y + *perp_wall_dist * rc.ray_dir.y;
	}
	else
	{
		*perp_wall_dist = rc.side_dist.y - rc.delta_dist.y;
		wall_x = p->pos.x + *perp_wall_dist * rc.ray_dir.x;
	}
	wall_x -= floor((wall_x));
	tex_x = (int)(wall_x * 64.0);
	//if((side == 'W' || side == 'E') && rc.ray_dir.x > 0) 
	//	tex_x = 64 - tex_x - 1;
	//if((side == 'N' || side == 'S') && rc.ray_dir.y < 0)
	//	tex_x = 64 - tex_x - 1;
	return (tex_x);
}

/*4-Given the x or y side, it returns the N, S, E or W char we need.*/
static char	get_final_side(char side, t_v2d ray_dir)
{
	if (side == 'y')
	{
		if (ray_dir.x < 0)
			side = 'E';
		else
			side = 'W';
	}
	else
	{	
		if (ray_dir.y < 0)
			side = 'S';
		else
			side = 'N';
	}
	return (side);
}

/*3-Checks for a wall hit and which side was hit, while also adding
to the distance the ray crossed and returns the side hit.*/
char	hit_find(t_raycast *rc, int map[24][24])
{
	int		hit;
	char	side;

	hit = 0;
	side = '\0';
	while (!hit)
	{
		if (rc->side_dist.x < rc->side_dist.y)
		{
			rc->map.x += rc->step.x;
			rc->side_dist.x += rc->delta_dist.x;
			side = 'y';
		}
		else
		{
			rc->map.y += rc->step.y;
			rc->side_dist.y += rc->delta_dist.y;
			side = 'x';
		}
		if (map[rc->map.y][rc->map.x] == 1)
			hit = 1;
	}
	return (get_final_side(side, (rc->ray_dir)));
}
