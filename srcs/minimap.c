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

#include "../include/libc3d.h"

/*Prepares the FOV triangle coordinates for use in the next function and
paint the square corresponding to the player.*/
void	ft_cone(t_app *p)
{
	t_v2d	player;
	t_v2d	lft_vert;
	t_v2d	rgt_vert;

	player.x = (double)(MAP_W - (MAP_W / 12));
	player.y = (double)(MAP_H - (MAP_W / 12));
	lft_vert.x = p->dir.x + p->plane.x * -1;
	lft_vert.y = p->dir.y + p->plane.y * -1;
	rgt_vert.x = p->dir.x + p->plane.x * 1;
	rgt_vert.y = p->dir.y + p->plane.y * 1;
	lft_vert.x = lft_vert.x * (MAP_W / 100 + 2) + player.x;
	lft_vert.y = lft_vert.y * (MAP_W / 100 + 2) + player.y;
	rgt_vert.x = rgt_vert.x * (MAP_W / 100 + 2) + player.x;
	rgt_vert.y = rgt_vert.y * (MAP_W / 100 + 2) + player.y;
	fill_cone(player, lft_vert, rgt_vert, p);
	my_pixel_put(&p->mlx.data, MAP_W - (MAP_W / 12) + 1, MAP_H - (MAP_W / 12) + 1, CLR_P);
	my_pixel_put(&p->mlx.data, MAP_W - (MAP_W / 12) + 1, MAP_H - (MAP_W / 12), CLR_P);
	my_pixel_put(&p->mlx.data, MAP_W - (MAP_W / 12) + 1, MAP_H - (MAP_W / 12) - 1, CLR_P);
	my_pixel_put(&p->mlx.data, MAP_W - (MAP_W / 12), MAP_H - (MAP_W / 12) + 1, CLR_P);
	my_pixel_put(&p->mlx.data, MAP_W - (MAP_W / 12), MAP_H - (MAP_W / 12), 0xffffff);
	my_pixel_put(&p->mlx.data, MAP_W - (MAP_W / 12), MAP_H - (MAP_W / 12) - 1, CLR_P);
	my_pixel_put(&p->mlx.data, MAP_W - (MAP_W / 12) - 1, MAP_H - (MAP_W / 12) + 1, CLR_P);
	my_pixel_put(&p->mlx.data, MAP_W - (MAP_W / 12) - 1, MAP_H - (MAP_W / 12), CLR_P);
	my_pixel_put(&p->mlx.data, MAP_W - (MAP_W / 12) - 1, MAP_H - (MAP_W / 12) - 1, CLR_P);
}

/*Creates a circular version of the minimap*/
static void	in_circle(t_img *data, t_v2i p, int color)
{
	double	x;

	x = fabs(sqrt(pow((MAP_W - (MAP_W / 12)) - p.x, 2) + pow((MAP_H - (MAP_W / 12)) - p.y, 2)));
	x = round(x);
	if (x < MAP_W / 21)
		my_pixel_put(data, p.x, p.y, color);
	else if (x <= MAP_W / 21 + 1)
		my_pixel_put(data, p.x, p.y, 0);
}

/*Loops through a quarter of the map and selects the right color of the pixel
  based on its position relative to the center (player)*/
void	minimap_painter(t_v2d player_xy, t_v2i start, t_app *p, int sign_x)
{
	start.x = MAP_W - (MAP_W / 12);
	player_xy.x = p->pos.x;
	while (start.x >= MAP_W - (MAP_W / 12) - MAP_W / 20 && start.x < MAP_W - (MAP_W / 12) + MAP_W / 20)
	{
		if (player_xy.x < 0 || player_xy.y < 0
			|| player_xy.x >= p->map.size_x || player_xy.y >= p->map.size_y
			|| p->map.data[(int) player_xy.y][(int) player_xy.x] == ' ')
			in_circle(&p->mlx.data, start, CLR_B);
		else if (p->map.data[(int) player_xy.y][(int) player_xy.x] == '0')
			in_circle(&p->mlx.data, start, CLR_F);
		else
			in_circle(&p->mlx.data, start, CLR_W);
		player_xy.x += (0.20 * sign_x);
		start.x += sign_x;
	}
}

/*calls itself with different signs to paint the minimap. Each call paints
a quarter of the minimap.*/
void	ft_minimap(t_app *p, int sign_x, int sign_y)
{
	t_v2d	player_xy;
	t_v2i	start;

	player_xy.y = p->pos.y;
	start.y = MAP_H - (MAP_W / 12);
	while (start.y >= MAP_H - (MAP_W / 12) - MAP_W / 20 && start.y < MAP_H - (MAP_W / 12) + MAP_W / 20)
	{
		minimap_painter(player_xy, start, p, sign_x);
		player_xy.y += (0.20 * sign_y);
		start.y += sign_y;
	}
	if (sign_x != 1 || sign_y != 1)
	{
		ft_cone(p);
		return ;
	}
	ft_minimap(p, -1, -1);
	ft_minimap(p, 1, -1);
	ft_minimap(p, -1, 1);
}
