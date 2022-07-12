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

#include "../headers/Cub3D.h"
#include "../headers/libft.h"

//4- Calculates lowest and highest pixel to fill in current stripe (ceiling,
//wall and floor).
static void	ft_drawing(int line_height, char side, int x, t_player *p, int tex_x)
{
	t_data	img_data;
	int		draw_start;
	int		draw_end;
	int		color;
	int		painter;

	img_data = handle_new_image(p->mlx[2]);
	draw_start = -line_height / 2 + map_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + map_height / 2;
	if (draw_end >= map_height)
		draw_end = map_height - 1;
	// How much to increase the texture coordinate per screen pixel
	double step = 1.0 * 64 / line_height;
	// Starting texture coordinate
	double texPos = (draw_start - map_height / 2 + line_height / 2) * step;
	painter = 0;
	while (painter != draw_start)
		my_pixel_put(&img_data, map_width - x - 1, painter++, 0x4287f5);
	
	while (painter <= draw_end)
	{
		if (side == 'N')
			color = *(get_img_pixel(&(p->tex_data[0]), tex_x, (int) texPos));
		else if (side == 'S')
			color = *(get_img_pixel(&(p->tex_data[1]), tex_x, (int) texPos));
		else if (side == 'W')
			color = *(get_img_pixel(&(p->tex_data[2]), tex_x, (int) texPos));
		else
			color = *(get_img_pixel(&(p->tex_data[3]), tex_x, (int) texPos));
		texPos += step;
		my_pixel_put(&img_data, map_width - x - 1, painter++, color);
	}	
	while (painter < map_height)
		my_pixel_put(&img_data, map_width - x - 1, painter++, 0x3fb821);
}


/*3-Checks for a wall hit and which side was hit, while also adding
to the distance the ray crossed and returns the side hit.*/
static char	hit_find(t_raycast *rc, int world_map[24][24])
{
	int		hit;
	char	side;

	hit = 0;
	side = '\0';
	while (!hit)
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->map_x += rc->step_x;
			rc->side_dist_x += rc->delta_dist_x;
			side = 'y';
		}
		else
		{
			rc->map_y += rc->step_y;
			rc->side_dist_y += rc->delta_dist_y;
			side = 'x';
		}
		if (world_map[rc->map_y][rc->map_x] == 1)
			hit = 1;
	}
	if (side == 'y')
	{
		if (rc->ray_dir_x < 0)
			side = 'E';
		else
			side = 'W';
	}
	else
	{	
		if (rc->ray_dir_y < 0)
			side = 'S';
		else
			side = 'N';
	}
	return (side);
}

/*2- Calcultates initial distance of the player to the x and y side considering
the movement vector (necessary to have the total distance to the wall) and
defines the direction of the x and y step.*/
static void	side_dist_calc(t_player *p, t_raycast *rc)
{
	rc->map_x = (int)p->pos_x;
	rc->map_y = (int)p->pos_y;
	if (rc->ray_dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (p->pos_x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - p->pos_x) * rc->delta_dist_x;
	}
	if (rc->ray_dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (p->pos_y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - p->pos_y) * rc->delta_dist_y;
	}
}

/*1- Calculates delta_x and delta_y, which represent the distance between
two x and y coordinates respectively that the ray will have to traverse
considering the movement vector.*/
static void	delta_calc(int x, t_player *p, int world_map[24][24])
{
	double		camera_x;
	t_raycast	rc;
	char		side;
	double		perp_wall_dist;

	camera_x = 2 * x / (double)map_width - 1;
	rc.ray_dir_x = p->dir_x + p->cam_plane.dir_x * camera_x;
	rc.ray_dir_y = p->dir_y + p->cam_plane.dir_y * camera_x;
	if (rc.ray_dir_x != 0)
		rc.delta_dist_x = fabs(1 / rc.ray_dir_x);
	else
		rc.delta_dist_x = 1e30;
	if (rc.ray_dir_y != 0)
		rc.delta_dist_y = fabs(1 / rc.ray_dir_y);
	else
		rc.delta_dist_y = 1e30;
	side_dist_calc(p, &rc);
	side = hit_find(&rc, world_map);
	if (side == 'W' || side == 'E')
		perp_wall_dist = rc.side_dist_x - rc.delta_dist_x;
	else
		perp_wall_dist = rc.side_dist_y - rc.delta_dist_y;
	double wall_x; //where exactly the wall was hit
	if (side == 'W' || side == 'E')
		wall_x = p->pos_y + perp_wall_dist * rc.ray_dir_y;
	else
		wall_x = p->pos_x + perp_wall_dist * rc.ray_dir_x;
	wall_x -= floor((wall_x));
	//x coordinate on the texture
	int tex_x = (int)(wall_x * 64.0);
	//if((side == 'W' || side == 'E') && rc.ray_dir_x > 0) 
	//	tex_x = 64 - tex_x - 1;
	//if((side == 'N' || side == 'S') && rc.ray_dir_y < 0)
	//	tex_x = 64 - tex_x - 1;
	ft_drawing((int)(map_height / perp_wall_dist), side, x, p, tex_x);
}

void	raycaster(t_player *p, int world_map[24][24])
{
	int	x;

	x = 0;
	while (x < map_width)
	{
		delta_calc(x++, p, world_map);
	}
}
