/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_draw_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:15:14 by daalmeid          #+#    #+#             */
/*   Updated: 2022/07/18 13:25:23 by marvin           ###   ########.fr       */
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
