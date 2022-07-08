/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_draw_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:15:14 by daalmeid          #+#    #+#             */
/*   Updated: 2022/07/08 13:33:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Cub3D.h"
#include "../headers/libft.h"

t_data	handle_new_image(void *mlx_image)
{
	t_data	data;

	data.addr = mlx_get_data_addr(mlx_image, &data.bpp,
			&data.line_length, &data.endian);
	return (data);
}

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	char	*pixel;

	pixel = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)pixel = color;
}

unsigned int	*get_img_pixel(t_data *data, int x, int y)
{
	char	*pixel;

	pixel = data->addr + (y * data->line_length + x * (data->bpp / 8));
	return ((unsigned int *) pixel);
}