/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_draw_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:15:14 by daalmeid          #+#    #+#             */
/*   Updated: 2022/07/06 13:21:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Cub3D.h"
#include "../headers/libft.h"

t_data	handle_new_image(void **mlx)
{
	t_data	data;

	data.addr = mlx_get_data_addr(mlx[2], &data.bpp,
			&data.line_length, &data.endian);
	return (data);
}

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	char	*pixel;

	pixel = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)pixel = color;
}
