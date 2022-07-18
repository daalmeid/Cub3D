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
	int		color;

	if (tex->side == 'N')
		color = *(get_img_pixel(&(p->tex[0]), tex->x, (int) tex->pos));
	else if (tex->side == 'S')
		color = *(get_img_pixel(&(p->tex[1]), tex->x, (int) tex->pos));
	else if (tex->side == 'W')
		color = *(get_img_pixel(&(p->tex[2]), tex->x, (int) tex->pos));
	else
		color = *(get_img_pixel(&(p->tex[3]), tex->x, (int) tex->pos));
	tex->pos += tex->step;
	my_pixel_put(&p->mlx.data, MAP_W - x - 1, painter, color);
}

//6- Calculates lowest and highest pixel to fill in current stripe (ceiling,
//wall and floor).
void	ft_drawing(int line_height, t_tex_rc_info tex, int x, t_app *p)
{
	int		draw_start;
	int		draw_end;
	int		painter;

	draw_start = -line_height / 2 + MAP_H / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + MAP_H / 2;
	if (draw_end >= MAP_H)
		draw_end = MAP_H - 1;
	tex.step = 1.0 * 64 / line_height;
	tex.pos = (draw_start - MAP_H / 2 + line_height / 2) * tex.step;
	painter = 0;
	while (painter != draw_start)
		my_pixel_put(&p->mlx.data, MAP_W - x - 1, painter++, 0x4287f5);
	while (painter < draw_end)
		wall_painter(painter++, x, &tex, p);
	while (painter < MAP_H)
		my_pixel_put(&p->mlx.data, MAP_W - x - 1, painter++, 0x3fb821);
}
