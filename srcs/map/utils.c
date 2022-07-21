/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:17:16 by marvin            #+#    #+#             */
/*   Updated: 2022/07/21 16:24:28 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d_map.h"

/* Clean all the memory related to the map file */
void	map_clean(t_app *p, int fd, char const *line)
{
	size_t	i;

	if (fd >= 0)
		close(fd);
	if (line)
		free((char *)line);
	if (p->tex[PATH_NO].path)
		free(p->tex[PATH_NO].path);
	if (p->tex[PATH_SO].path)
		free(p->tex[PATH_SO].path);
	if (p->tex[PATH_EA].path)
		free(p->tex[PATH_EA].path);
	if (p->tex[PATH_WE].path)
		free(p->tex[PATH_WE].path);
	i = 0;
	while (i < p->map.size_y)
		free(p->map.data[i++]);
	free(p->map.data);
}

/* A simple realloc suited for reading the map */
char	**readmap_realloc(char **src, size_t bytes)
{
	char	**buff;
	size_t	i;

	if (!src)
		return (NULL);
	buff = (char **)malloc(sizeof(char *) * bytes);
	if (!buff)
		return (NULL);
	i = 0;
	while (i < bytes && src[i])
	{
		buff[i] = src[i];
		i++;
	}
	while (i < bytes)
		buff[i++] = 0;
	return (buff);
}

/* Returns true if c equals space (' ') */
int	ft_isblank(int c)
{
	return (c == ' ');
}

/* Check if a line only contains spaces */
int	ft_empty_line(char const *s)
{
	while (*s && *s != '\n')
	{
		if (!ft_isblank(*s))
			return (false);
		s++;
	}
	return (true);
}

/* Increment iter starting at += begin bytes for each space in p */
void	ft_hop_blank(char *p, size_t begin, size_t *iter)
{
	*iter += begin;
	while (ft_isblank(p[*iter]))
		(*iter) += 1;
	*iter -= begin;
}
