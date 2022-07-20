/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:12:36 by marvin            #+#    #+#             */
/*   Updated: 2022/07/19 18:12:37 by marvin           ###   ########.fr       */
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
	// map_clean(&mp); // Remove later
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

// int	main(int argc, char **argv)
// {
// 	t_map	map;
// 	char	*tmp;

// 	if (argc == 2)
// 	{
// 		tmp = (argv[1]) + (ft_strlen(argv[1]) - 4);
// 		if (tmp <= argv[1] || ft_strncmp(tmp, ".cub", 5) != 0)
// 		{
// 			ft_putstr_fd("Error\nUnknown map file extension\n", STDERR_FILENO);
// 			exit(1);
// 		}
// 		ft_memset(&map, 0, sizeof(t_map));
// 		readmap(argv[1], &map);
// 	}
// 	else
// 	{
// 		ft_putstr_fd("Error\nUsage: ./prog *.cub\n", STDERR_FILENO);
// 		exit (1);
// 	}
// 	return (0);
// }
