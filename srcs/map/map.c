/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:12:36 by marvin            #+#    #+#             */
/*   Updated: 2022/07/21 15:21:53 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d_map.h"

static void	readmap_init(t_mp *mp, t_app *p, char const *file);

/* open file and check if map is valid */
void	readmap(t_app *p, char const *file)
{
	t_mp	mp;

	readmap_init(&mp, p, file);
	readmap_info(&mp);
	readmap_content(&mp);
	close(mp.fd);
	mp.fd = -1;
	readmap_resize(&mp);
	readmap_verify(&mp);
	if (p->pos.x == -1)
		map_error(1, "No player position provided", &mp);
}

/* Initialize variables */
static void	readmap_init(t_mp *mp, t_app *p, char const *file)
{
	ft_memset(mp, 0, sizeof(t_mp));
	mp->fd = open(file, O_RDONLY);
	if (mp->fd == -1)
		werror(1, file, true);
	mp->file = (char *)file;
	mp->p = p;
	mp->p->clr_ceil = UINT_MAX;
	mp->p->clr_floor = UINT_MAX;
	mp->off_l = INT_MAX;
	mp->p->pos.x = -1;
}
