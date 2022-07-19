#ifndef C3D_MAP_H
# define C3D_MAP_H

# include "../../cub3D/srcs/libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <errno.h>

typedef unsigned int uint;

enum
{
	PATH_NO,
	PATH_SO,
	PATH_EA,
	PATH_WE
};

typedef struct s_map
{
	char	**data;
	char	*path[4];
	size_t	size_x;
	size_t	size_y;
	int		floor_color;
	int		ceil_color;
	double	player_x;
	double	player_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;

}			t_map;

typedef struct s_mp
{
	int		fd;
	t_map	*map;
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
void	map_clean(t_mp *mp);
int		werror(int code, char const *s, bool syserr);
int 	map_error(int code, char const *s, t_mp *mp);

void	readmap(char const *file, t_map *map);
void	readmap_info(t_mp *mp);
void	readmap_content(t_mp *mp);
void	readmap_resize(t_mp *mp);
void	readmap_verify(t_mp *mp);

#endif
