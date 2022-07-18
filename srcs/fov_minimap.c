/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:48:09 by marvin            #+#    #+#             */
/*   Updated: 2022/07/18 16:48:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libc3d.h"

static double	ft_min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

static double	ft_max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

/*Finds the b value of the y = mx + b equation.*/
static double	get_lineb(t_v2d const a, t_v2d const b)
{	
	double	line_b;

	if (b.x - a.x == 0)
		line_b = 0;
	else
		line_b = ((b.y - a.y) * b.x + ((b.x - a.x) * b.y) * -1)
			/ ((b.x - a.x) * -1);
	return (line_b);
}

/*Uses the binary space partitioning method to find if coord belongs to
the FOV. if so, returns true.*/
static bool	bsp(t_v2d a, t_v2d b, t_v2d c, t_v2d coord)
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

/*Runs through the coordinates where the FOV is located, by finding its max
and min y and x value.*/
void	fill_cone(t_v2d player, t_v2d lft_vert, t_v2d rgt_vert, t_app *p)
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
				my_pixel_put(&p->mlx.data, (int) coord.x,
					(int) coord.y, CLR_L);
			coord.x += 1.0;
		}
		coord.x = min.x;
		coord.y += 1.0;
	}
}
