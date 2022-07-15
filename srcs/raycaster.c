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

#include "../includes/libc3d.h"

//4- Calculates lowest and highest pixel to fill in current stripe (ceiling,
//wall and floor).
static void	ft_drawing(int line_height, char side, int x, t_app *p, int tex_x)
{
	int		draw_start;
	int		draw_end;
	int		color;
	int		painter;

	draw_start = -line_height / 2 + MAP_H / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + MAP_H / 2;
	if (draw_end >= MAP_H)
		draw_end = MAP_H - 1;
	// How much to increase the texture coordinate per screen pixel
	double step = 1.0 * 64 / line_height;
	// Starting texture coordinate
	double texPos = (draw_start - MAP_H / 2 + line_height / 2) * step;
	painter = 0;
	while (painter != draw_start)
		my_pixel_put(&p->mlx.data, MAP_W - x - 1, painter++, 0x4287f5);
	while (painter < draw_end)
	{
		if (side == 'N')
			color = *(get_img_pixel(&(p->tex[0]), tex_x, (int) texPos));
		else if (side == 'S')
			color = *(get_img_pixel(&(p->tex[1]), tex_x, (int) texPos));
		else if (side == 'W')
			color = *(get_img_pixel(&(p->tex[2]), tex_x, (int) texPos));
		else
			color = *(get_img_pixel(&(p->tex[3]), tex_x, (int) texPos));
		texPos += step;
		my_pixel_put(&p->mlx.data, MAP_W - x - 1, painter++, color);
	}	
	while (painter < MAP_H)
		my_pixel_put(&p->mlx.data, MAP_W - x - 1, painter++, 0x3fb821);
}

/*3-Checks for a wall hit and which side was hit, while also adding
to the distance the ray crossed and returns the side hit.*/
static char	hit_find(t_raycast *rc, int map[24][24])
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
	if (side == 'y')
	{
		if (rc->ray_dir.x < 0)
			side = 'E';
		else
			side = 'W';
	}
	else
	{	
		if (rc->ray_dir.y < 0)
			side = 'S';
		else
			side = 'N';
	}
	return (side);
}

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
considering the movement vector.*/
static void	delta_calc(int x, t_app *p, int map[24][24])
{
	double		camera_x;
	t_raycast	rc;
	char		side;
	double		perp_wall_dist;

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
	side = hit_find(&rc, map);
	if (side == 'W' || side == 'E')
		perp_wall_dist = rc.side_dist.x - rc.delta_dist.x;
	else
		perp_wall_dist = rc.side_dist.y - rc.delta_dist.y;
	double wall_x; //where exactly the wall was hit
	if (side == 'W' || side == 'E')
		wall_x = p->pos.y + perp_wall_dist * rc.ray_dir.y;
	else
		wall_x = p->pos.x + perp_wall_dist * rc.ray_dir.x;
	wall_x -= floor((wall_x));
	//x coordinate on the texture
	int tex_x = (int)(wall_x * 64.0);
	//if((side == 'W' || side == 'E') && rc.ray_dir.x > 0) 
	//	tex_x = 64 - tex_x - 1;
	//if((side == 'N' || side == 'S') && rc.ray_dir.y < 0)
	//	tex_x = 64 - tex_x - 1;
	ft_drawing((int)(MAP_H / perp_wall_dist), side, x, p, tex_x);
}

void	raycaster(t_app *p, int map[24][24])
{
	int	x;

	x = 0;
	while (x < MAP_W)
		delta_calc(x++, p, map);
}
