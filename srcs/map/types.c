/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:16:24 by marvin            #+#    #+#             */
/*   Updated: 2022/07/25 16:24:22 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d_map.h"

static int	readrgb(t_mp *mp, char type);
static int	readnum(t_mp *mp);
static char	*readword(t_mp *mp, int indx);
static void	readmap_match(t_mp *mp);

/*	
	Read file searching for allowed types 
	and collect their respective information 
	gives an error if any unexpected text is found
*/
void	readmap_info(t_mp *mp)
{
	while (mp->count != 6)
	{
		mp->line = get_next_line(mp->fd);
		if (!mp->line)
		{
			if (errno != 0)
				map_error(1, NULL, mp);
			else
				map_error(1, "unexpected end of file\n", mp);
		}
		else if (!ft_empty_line(mp->line))
			readmap_match(mp);
		mp->col = 0;
		free(mp->line);
		mp->line = NULL;
		mp->ln += 1;
	}
}

/* Compares the given string to the known types 
	gives an error if not found */
static void	readmap_match(t_mp *mp)
{
	if (mp->line[0] == 'F')
		mp->p->clr_floor = readrgb(mp, 'F');
	else if (mp->line[0] == 'C')
		mp->p->clr_ceil = readrgb(mp, 'C');
	else if (ft_strncmp(mp->line, "NO", 2) == 0)
		mp->p->tex[TEX_NO].path = readword(mp, TEX_NO);
	else if (ft_strncmp(mp->line, "SO", 2) == 0)
		mp->p->tex[TEX_SO].path = readword(mp, TEX_SO);
	else if (ft_strncmp(mp->line, "EA", 2) == 0)
		mp->p->tex[TEX_EA].path = readword(mp, TEX_EA);
	else if (ft_strncmp(mp->line, "WE", 2) == 0)
		mp->p->tex[TEX_WE].path = readword(mp, TEX_WE);
	else
		map_error(1, "unknown type identifier\n", mp);
	mp->count += 1;
}

/* Collects the file path word for the respective texture */
static char	*readword(t_mp *mp, int indx)
{
	char	*cp;
	int		len;

	if (mp->p->tex[indx].path != NULL)
		map_error(1, "duplicated field\n", mp);
	len = 0;
	mp->col += 2;
	ft_hop_blank(mp->line, 0, &mp->col);
	while (!ft_isblank(mp->line[mp->col + len])
		&& mp->line[mp->col + len] != '\n')
		len++;
	mp->col += len;
	if (len == 0)
		map_error(1, "must provide a valid texture path\n", mp);
	if (mp->line[mp->col] != '\n')
		map_error(1, "missing expected character '\\n'\n", mp);
	cp = (char *)malloc(sizeof(char) * (len + 1));
	if (!cp)
		map_error(1, NULL, mp);
	ft_strlcpy(cp, &mp->line[mp->col - len], len + 1);
	return (cp);
}

/* Collects the rgb value formatted as 0,125,255 from the given string */
static int	readrgb(t_mp *mp, char type)
{
	int	i;
	int	val;

	i = 0;
	val = 0;
	mp->col += 1;
	if ((type == 'C' && mp->p->clr_ceil != UINT_MAX)
		|| (type == 'F' && mp->p->clr_floor != UINT_MAX))
		map_error(1, "duplicated field\n", mp);
	ft_hop_blank(mp->line, 0, &mp->col);
	while (i < 3)
	{
		val = (val << 8) + readnum(mp);
		i++;
		if (i != 3 && mp->line[mp->col] != ',')
			map_error(1, "missing expected character ','\n", mp);
		else if (i != 3)
			mp->col += 1;
	}
	if (mp->line[mp->col] != '\n')
		map_error(1, "missing expected character '\\n'\n", mp);
	return (val);
}

/* Converts a 3 digit number in 0-255 range */
static int	readnum(t_mp *mp)
{
	size_t	j;
	int		n;

	n = 0;
	j = 0;
	while (ft_isdigit(mp->line[mp->col + j]))
		j++;
	if (j == 0)
		map_error(1, "must provide a valid R,G,B color value\n", mp);
	if (j > 3)
		map_error(1, "color value has more then 3 digits\n", mp);
	while (j--)
		n = (n * 10) + (mp->line[mp->col++] - '0');
	if (n > 255)
		map_error(1, "out of range color value\n", mp);
	return (n);
}
