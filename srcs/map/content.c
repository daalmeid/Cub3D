/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:10:59 by marvin            #+#    #+#             */
/*   Updated: 2022/07/19 18:11:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d_map.h"

static void	readmap_line(t_mp *mp, size_t chunk, bool blank_line);
static void	readmap_adjust_y(t_mp *mp, size_t chunk);

/*
	read the map content
	throw an error for any unexpected format
*/
void	readmap_content(t_mp *mp)
{
	size_t	chunk;
	bool	blank_line;

	blank_line = false;
	mp->map->size_y = 0;
	chunk = 10;
	mp->map->data = (char **)ft_calloc(chunk, sizeof(char *));
	if (!mp->map->data)
		map_error(1, NULL, mp);
	while (1)
	{
		mp->map->data[mp->map->size_y] = get_next_line(mp->fd);
		if (!mp->map->data[mp->map->size_y])
		{
			if (errno != 0)
				map_error(1, NULL, mp);
			break ;
		}
		readmap_line(mp, chunk, blank_line);
	}
	readmap_adjust_y(mp, chunk);
}

/* handle each line */
static void	readmap_line(t_mp *mp, size_t chunk, bool blank_line)
{
	char	**tmp;

	if (ft_empty_line(mp->map->data[mp->map->size_y]))
	{
		if (mp->map->size_y != 0)
			blank_line = true;
		free(mp->map->data[mp->map->size_y]);
		mp->map->data[mp->map->size_y] = 0;
		mp->ln += 1;
		return ;
	}
	if (blank_line)
		map_error(1, "unexpected bytes after map content\n", mp);
	mp->ln += 1;
	if (mp->map->size_y == (chunk - 1))
	{
		chunk *= 10;
		tmp = readmap_realloc(mp->map->data, chunk);
		if (!tmp)
			map_error(1, NULL, mp);
		free(mp->map->data);
		mp->map->data = tmp;
	}
	mp->map->size_y++;
}

/* adjust the allocated memory to fit the map */
static void	readmap_adjust_y(t_mp *mp, size_t chunk)
{
	char	**tmp;

	if (mp->map->size_y != chunk - 1)
	{
		tmp = readmap_realloc(mp->map->data, mp->map->size_y);
		if (!tmp)
			map_error(1, NULL, mp);
		free(mp->map->data);
		mp->map->data = tmp;
	}
}
