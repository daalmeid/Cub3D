/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_draw_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:15:14 by daalmeid          #+#    #+#             */
/*   Updated: 2022/07/25 16:11:46 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libc3d.h"

bool	handle_new_image(t_img *dst, void *mlx)
{
	dst->ptr = mlx_xpm_file_to_image(mlx, dst->path, &dst->width, &dst->height);
	if (!dst->ptr)
		return (false);
	dst->addr = mlx_get_data_addr(dst->ptr, &dst->bpp,
			&dst->line_length, &dst->endian);
	if (!dst->addr)
		return (false);
	return (true);
}

void	my_pixel_put(t_img *data, int x, int y, int color)
{
	char	*pixel;

	pixel = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)pixel = color;
}

unsigned int	*get_img_pixel(t_img *data, int x, int y)
{
	char	*pixel;

	pixel = data->addr + (y * data->line_length + x * (data->bpp / 8));
	return ((unsigned int *) pixel);
}

/* Draw image from pos (left top corner) rescaling to size */
void	draw_image(t_app *p, t_img *img, t_v2i pos, t_v2i size)
{
	t_v2d	posd;
	t_v2i	put;
	t_v2d	incr;
	t_uint	color;

	posd.y = 0;
	put.y = pos.y;
	incr.x = fabs((double)img->width / size.x);
	incr.y = fabs((double)img->height / size.y);
	while (put.y < pos.y + size.y)
	{
		posd.x = 0;
		put.x = pos.x;
		while (put.x < pos.x + size.x)
		{
			color = *get_img_pixel(img, (int)(posd.x), (int)(posd.y));
			if (color != 0xff000000)
				my_pixel_put(&p->mlx.data, put.x, put.y, color);
			posd.x += incr.x;
			put.x += 1;
		}
		posd.y += incr.y;
		put.y += 1;
	}
}
