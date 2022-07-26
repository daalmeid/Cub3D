/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_painter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:03:58 by marvin            #+#    #+#             */
/*   Updated: 2022/07/18 17:03:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libc3d.h"

/*7- Gets the correct color from the base texture to put on our image*/
static void	wall_painter(int painter, int x, t_tex_rc_info *tex, t_app *p)
{
	int	color;

	if (tex->side == TEX_NO)
		color = *(get_img_pixel(&(p->tex[TEX_NO]), tex->x, (int) tex->pos));
	else if (tex->side == TEX_SO)
		color = *(get_img_pixel(&(p->tex[TEX_SO]), tex->x, (int) tex->pos));
	else if (tex->side == TEX_EA)
		color = *(get_img_pixel(&(p->tex[TEX_EA]), tex->x, (int) tex->pos));
	else
		color = *(get_img_pixel(&(p->tex[TEX_WE]), tex->x, (int) tex->pos));
	tex->pos += tex->step;
	if ((unsigned int) color == 0xff000000)
	{
		if (painter < MAP_H / 2)
			color = p->clr_ceil;
		else
			color = p->clr_floor;
	}
	else if (tex->side == TEX_NO || tex->side == TEX_SO)
		color = (int)((color & 0x0000FF) * 0.70)
			| (int)(((color >> 8) & 0x0000FF) * 0.70) << 8
			| (int)((color >> 16) * 0.70) << 16;
	my_pixel_put(&p->mlx.data, MAP_W - x - 1, painter, color);
}

//6- Calculates lowest and highest pixel to fill in current stripe (ceiling,
//wall and floor).
void	ft_drawing(int line_height, t_tex_rc_info *tex, int x, t_app *p)
{
	int		draw_start;
	int		draw_end;
	int		painter;

	draw_start = (-line_height + round(p->mouse.y)) / 2 + MAP_H / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (line_height + round(p->mouse.y)) / 2 + MAP_H / 2;
	if (draw_end > MAP_H)
		draw_end = MAP_H;
	tex->step = (double)(p->tex[tex->side].height) / line_height;
	tex->pos = (draw_start - (MAP_H + round(p->mouse.y)) / 2
			+ line_height / 2) * tex->step;
	if (tex->pos < 0)
		tex->pos = 0;
	painter = 0;
	while (painter < draw_start)
		my_pixel_put(&p->mlx.data, MAP_W - x - 1, painter++, p->clr_ceil);
	while (painter < draw_end)
		wall_painter(painter++, x, tex, p);
	while (painter < MAP_H)
		my_pixel_put(&p->mlx.data, MAP_W - x - 1, painter++, p->clr_floor);
}
