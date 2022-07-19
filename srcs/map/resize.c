/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:14:22 by marvin            #+#    #+#             */
/*   Updated: 2022/07/19 18:14:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d_map.h"

static void	readmap_adjust_x(t_mp *mp);
static void	resize_calculate(t_mp *mp, size_t row);

void	readmap_resize(t_mp *mp)
{
	size_t	row;

	row = 0;
	if (mp->map->size_y < 3)
		map_error(0, "map height is too small\n", mp);
	while (row < mp->map->size_y)
		resize_calculate(mp, row++);
	mp->sx -= mp->off_l;
	mp->map->size_x = mp->sx;
	if (mp->map->size_x < 3)
		map_error(0, "map width is too small\n", mp);
	readmap_adjust_x(mp);
}

static void	resize_calculate(t_mp *mp, size_t row)
{
	size_t	i;
	size_t	j;

	j = 0;
	ft_hop_blank(mp->map->data[row], 0, &j);
	if (mp->off_l > j)
		mp->off_l = j;
	i = j;
	j = 0;
	while (1)
	{
		while (!ft_isblank(mp->map->data[row][i])
			&& mp->map->data[row][i] && mp->map->data[row][i] != '\n')
			i++;
		ft_hop_blank(mp->map->data[row], i, &j);
		if (mp->map->data[row][i + j] == '\n' || !mp->map->data[row][i + j])
			break ;
		i += j;
		j = 0;
	}
	if (i > mp->sx)
		mp->sx = i;
}

static void	readmap_adjust_x(t_mp *mp)
{
	size_t	i;
	size_t	row;
	char	*tmp;

	row = 0;
	while (row < mp->map->size_y)
	{
		i = 0;
		tmp = (char *)malloc(sizeof(char) * (mp->map->size_x + 1));
		if (!tmp)
			map_error(1, NULL, mp);
		while (mp->map->data[row][mp->off_l + i] != '\n'
			&& mp->map->data[row][i] != '\0' && (size_t)i < mp->map->size_x)
		{
			tmp[i] = mp->map->data[row][mp->off_l + i];
			i++;
		}
		while ((size_t)i < mp->map->size_x)
			tmp[i++] = ' ';
		tmp[i] = 0;
		free(mp->map->data[row]);
		mp->map->data[row] = tmp;
		row++;
	}
}
