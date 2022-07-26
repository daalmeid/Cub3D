/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:19:56 by daalmeid          #+#    #+#             */
/*   Updated: 2022/07/25 16:34:30 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libc3d.h"

void	cleaner(t_app *p)
{
	int	i;

	i = 0;
	if (p->mlx.win != NULL)
		mlx_destroy_window(p->mlx.ptr, p->mlx.win);
	if (p->mlx.data.ptr != NULL)
		mlx_destroy_image(p->mlx.ptr, p->mlx.data.ptr);
	while (i < TEX_COUNT && p->tex[i].ptr != NULL)
		mlx_destroy_image(p->mlx.ptr, p->tex[i++].ptr);
	mlx_destroy_display(p->mlx.ptr);
	free(p->mlx.ptr);
	map_clean(p, -1, NULL);
}
