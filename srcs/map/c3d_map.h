/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_map.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:49:08 by rafernan          #+#    #+#             */
/*   Updated: 2022/07/20 17:49:59 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef C3D_MAP_H
# define C3D_MAP_H

# include "../../include/libc3d.h"

typedef struct s_mp
{
	int		fd;
	t_app	*p;
	char	*file;
	char	*line;
	size_t	ln;
	size_t	col;
	int		count;
	size_t	off_l;
	size_t	sx;
}			t_mp;

/* Utils */
void	ft_hop_blank(char *p, size_t begin, size_t *iter);
int		ft_empty_line(char const *s);
int		ft_isblank(int c);
char	**readmap_realloc(char **src, size_t bytes);
void	map_clean(t_app *p, int fd, char const *line);
int		werror(int code, char const *s, bool syserr);
int		map_error(int code, char const *s, t_mp *mp);

void	readmap(t_app *map, char const *file);
void	readmap_info(t_mp *mp);
void	readmap_content(t_mp *mp);
void	readmap_resize(t_mp *mp);
void	readmap_verify(t_mp *mp);

#endif
