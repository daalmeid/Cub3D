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
int	get_tex_x(int side, t_raycast rc, t_app *p, double *perp_wall_dist)
{
	double	wall_x;
	int		tex_x;

	if (side == TEX_WE || side == TEX_EA)
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
	tex_x = (int)(wall_x * p->tex[side].width);
	if ((side == TEX_WE || side == TEX_EA)
		&& rc.ray_dir.x < 0)
		tex_x = p->tex[side].width - tex_x - 1;
	if ((side == TEX_NO || side == TEX_SO)
		&& rc.ray_dir.y > 0)
		tex_x = p->tex[side].width - tex_x - 1;
	return (tex_x);
}

/*4-Given the x or y side, it returns the N, S, E or W char we need.*/
static int	get_final_side(char side, t_v2d ray_dir)
{
	if (side == 'y')
	{
		if (ray_dir.x < 0)
			side = TEX_EA;
		else
			side = TEX_WE;
	}
	else
	{	
		if (ray_dir.y < 0)
			side = TEX_SO;
		else
			side = TEX_NO;
	}
	return (side);
}

/*3-Checks for a wall hit and which side was hit, while also adding
to the distance the ray TEX_CURSORed and returns the side hit.*/
char	hit_find(t_raycast *rc, char **map)
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
		if (map[rc->map.y][rc->map.x] == '1')
			hit = 1;
	}
	return (get_final_side(side, (rc->ray_dir)));
}
