/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:20:57 by marvin            #+#    #+#             */
/*   Updated: 2022/07/19 19:06:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d_map.h"

static void	set_player(t_mp *mp, size_t i, size_t j, char dir);
static int	isnearby(t_mp *mp, size_t x, size_t y, char c);
static void	set_orientation(t_mp *mp, char dir);

void	readmap_verify(t_mp *mp)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (j < mp->map->size_y)
	{
		i = 0;
		while (i < mp->map->size_x)
		{
			if (mp->map->data[j][i] == 'N' || mp->map->data[j][i] == 'S'
				|| mp->map->data[j][i] == 'W' || mp->map->data[j][i] == 'E')
				set_player(mp, i, j, mp->map->data[j][i]);
			else if (mp->map->data[j][i] != '0' && mp->map->data[j][i] != '1'
				&& mp->map->data[j][i] != ' ')
				map_error(1, "unknown map tile identifier\n", mp);
			if ((i == 0 || j == 0 || i == mp->map->size_x - 1
					|| j == mp->map->size_y - 1) && mp->map->data[j][i] != '1'
					&& mp->map->data[j][i] != ' ')
				map_error(1, "map is not surrounded by walls\n", mp);
			if (mp->map->data[j][i] == ' ' && isnearby(mp, i, j, '0'))
				map_error(1, "map is not surrounded by walls\n", mp);
			i++;
		}
		j++;
	}
}

/* check if any surrounding tile matches c */
static int	isnearby(t_mp *mp, size_t x, size_t y, char c)
{
	char	**map;

	map = mp->map->data;
	if (x != 0 && (map[y][x - 1] == c
		|| (y != 0 && map[y - 1][x - 1] == c))) /* left and left-up corner */
		return (true);
	if (x != mp->map->size_x -1 && (map[y][x + 1] == c
		|| (y != mp->map->size_y - 1 && map[y + 1][x + 1] == c))) /* right and down-right corner */
		return (true);
	if (y != 0 && (map[y - 1][x] == c
		|| (x != mp->map->size_x - 1 && map[y - 1][x + 1] == c))) // up and up-right corner
		return (true);
	if (y != mp->map->size_y - 1 && (map[y + 1][x] == c
		|| (x != 0 && map[y + 1][x - 1] == c))) // down and down-left corner
		return (true);
	return (false);
}

/* set player variables */
static void	set_player(t_mp *mp, size_t i, size_t j, char dir)
{
	(void)dir;
	if (mp->map->player_x != -1)
		map_error(1, "duplicated player spawn position\n", mp);
	if (isnearby(mp, i, j, ' '))
		map_error(1, "player spawn position is outside of map\n", mp);
	mp->map->player_x = i;
	mp->map->player_y = j;
	set_orientation(mp, dir);
}

static void	set_orientation(t_mp *mp, char dir)
{
	if (dir == 'E')
	{
		mp->map->dir_x = 1;
		mp->map->dir_y = 0;
	}
	else if (dir == 'W')
	{
		mp->map->dir_x = -1;
		mp->map->dir_y = 0;
	}
	else if (dir == 'S')
	{
		mp->map->dir_x = 0;
		mp->map->dir_y = 1;
	}
	else if (dir == 'N')
	{
		mp->map->dir_x = 0;
		mp->map->dir_y = -1;
	}
	mp->map->plane_y = (0.66 * mp->map->dir_x) * -(dir == 'E' || dir == 'W');
	mp->map->plane_x = (0.66 * mp->map->dir_y) * -(dir == 'E' || dir == 'W');
}
