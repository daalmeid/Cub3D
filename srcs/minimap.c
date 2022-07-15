/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:50:57 by marvin            #+#    #+#             */
/*   Updated: 2022/07/13 14:50:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libc3d.h"

double	ft_min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

double	ft_max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

/*Finds the b value of the y = mx + b equation.*/
static double	get_lineb(t_v2d const a, t_v2d const b) {
	
	double	line_b;

	if (b.x - a.x == 0)
		line_b = 0;
	else
		line_b = ((b.y - a.y) * b.x + ((b.x - a.x) * b.y) * -1)
		/ ((b.x - a.x) * -1);
	return line_b;
}

/*Uses the binary space partitioning method to find if coord belongs to
the FOV. if so, returns true.*/
bool	bsp(t_v2d a, t_v2d b, t_v2d c, t_v2d coord)
{	
	static int	depth = 0;
	double		line_deriv_c;
	double		line_deriv_test;
	double		line_b;

	if (depth == 3)
		depth = 0;
	line_b = get_lineb(a, b);
	line_deriv_c = (b.y - a.y) * c.x + ((b.x - a.x)
			* c.y * -1) + (b.x - a.x) * line_b;
	line_deriv_test = (b.y - a.y) * coord.x + ((b.x - a.x)
			* coord.y * -1) + (b.x - a.x) * line_b;
	if ((line_deriv_c <= 0 && line_deriv_test <= 0)
			|| (line_deriv_c > 0 && line_deriv_test > 0))
	{
		depth++;
		if (depth - 1 == 0)
			return (bsp(b, c, a, coord));
		else if (depth - 1 == 1)
			return (bsp(c, b, a, coord));
		else if (depth - 1 == 2)
			return (true);
	}
	depth = 0;
	return (false);
}

/*Runs through the coordinates where the FOV is located, by finding its max and min
y and x value.*/
void	fill_cone(t_v2d player, t_v2d lft_vert, t_v2d rgt_vert, t_player *p)
{
	t_v2d	min;
	t_v2d	max;
	t_v2d	coord;

	min.x = ft_min(ft_min(player.x, lft_vert.x), rgt_vert.x);
	min.y = ft_min(ft_min(player.y, lft_vert.y), rgt_vert.y);
	max.x = ft_max(ft_max(player.x, lft_vert.x), rgt_vert.x);
	max.y = ft_max(ft_max(player.y, lft_vert.y), rgt_vert.y);
	coord.x = min.x;
	coord.y = min.y;
	while (coord.y <= max.y)
	{
		while (coord.x <= max.x)
		{
			if (bsp(player, lft_vert, rgt_vert, coord) == true)
				my_pixel_put(&p->map_data, (int) coord.x,
					(int) coord.y, 0xeaf00a);
			coord.x += 1.0;
		}
		coord.x = min.x;
		coord.y += 1.0;
	}
}

/*Prepares the FOV triangle coordinates for use in the next function and paint the
square corresponding to the player.*/
void	ft_cone(t_player *p)
{
	t_v2d	player;
	t_v2d	lft_vert;
	t_v2d	rgt_vert;

	player.x = (double) (map_width - 70);
	player.y = (double) (map_height - 70);
	lft_vert.x = p->dir.x + p->plane.x * -1;
	lft_vert.y = p->dir.y +  p->plane.y * -1;
	rgt_vert.x = p->dir.x + p->plane.x * 1;
	rgt_vert.y = p->dir.y +  p->plane.y * 1;
	lft_vert.x = lft_vert.x * 12 + player.x;
	lft_vert.y = lft_vert.y * 12 + player.y;
	rgt_vert.x = rgt_vert.x * 12 + player.x;
	rgt_vert.y = rgt_vert.y * 12 + player.y;
	fill_cone(player, lft_vert, rgt_vert, p);
	my_pixel_put(&p->map_data, map_width - 71, map_height - 71, 0xff0000);
	my_pixel_put(&p->map_data, map_width - 71, map_height - 70, 0xff0000);
	my_pixel_put(&p->map_data, map_width - 71, map_height - 69, 0xff0000);
	my_pixel_put(&p->map_data, map_width - 70, map_height - 71, 0xff0000);
	my_pixel_put(&p->map_data, map_width - 70, map_height - 70, 0xff0000);
	my_pixel_put(&p->map_data, map_width - 70, map_height - 69, 0xff0000);
	my_pixel_put(&p->map_data, map_width - 69, map_height - 71, 0xff0000);
	my_pixel_put(&p->map_data, map_width - 69, map_height - 70, 0xff0000);
	my_pixel_put(&p->map_data, map_width - 69, map_height - 69, 0xff0000);
}

/*calls itself with different signs to paint the minimap. Each call paints a quarter of the
	minimap.*/
void	ft_minimap(t_player *p, int world_map[24][24], int sign_x, int sign_y)
{
	t_v2d	player_xy;
	t_v2i	start;

	player_xy.x = p->pos.x;
	player_xy.y = p->pos.y;
	start.y = map_height - 70;
	while (start.y >= map_height - 120 && start.y < map_height - 19)
	{
		start.x = map_width - 70;
		player_xy.x = p->pos.x;
		while (start.x >= map_width - 120 && start.x < map_width - 19)
		{
			if (player_xy.x < 0 || player_xy.y < 0 || player_xy.x > 24 || player_xy.y > 24)
				my_pixel_put(&p->map_data, start.x, start.y, 0x000000);
			else if (world_map[(int) player_xy.y][(int) player_xy.x] == 0)
				my_pixel_put(&p->map_data, start.x, start.y, 0x64a3e3);
			else
				my_pixel_put(&p->map_data, start.x, start.y, 0x0308a1);
			player_xy.x += (0.20 * sign_x);
			start.x += sign_x;
		}
		player_xy.y += (0.20 * sign_y);
		start.y += sign_y;
	}
	if (sign_x != 1 || sign_y != 1)
		return ;
	ft_minimap(p, world_map, -1, -1);
	ft_minimap(p, world_map, 1, -1);
	ft_minimap(p, world_map, -1, 1);
	ft_cone(p);
}