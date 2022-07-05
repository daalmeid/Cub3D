/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:09:03 by daalmeid          #+#    #+#             */
/*   Updated: 2022/01/28 13:19:03 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"

static char	*get_fline(char *final_line, char *buf)
{
	char	*tmp;
	char	*ptr;
	int		fl_strlen;

	if (*final_line == 0)
		ft_strlcat(final_line, (const char *) buf, BUFFER_SIZE + 1);
	else
	{
		fl_strlen = ft_strlen(final_line);
		tmp = calloc(sizeof(char), fl_strlen + BUFFER_SIZE + 1);
		if (!tmp)
			return (NULL);
		ft_strlcat(tmp, final_line, fl_strlen + BUFFER_SIZE + 1);
		ft_strlcat(tmp, (const char *) buf, fl_strlen + BUFFER_SIZE + 1);
		ptr = final_line;
		final_line = tmp;
		tmp = ptr;
		free (ptr);
	}
	return (final_line);
}

static char	*get_first_buf(char	*buf, int fd)
{
	char		*ptr;
	char		*final_line;

	if (BUFFER_SIZE < 0 || fd == -1)
		return (NULL);
	final_line = calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!final_line)
		return (NULL);
	if (buf[0] != 0)
	{
		ft_strlcat(final_line, (const char *) buf, (BUFFER_SIZE + 1));
		ptr = ft_strchr((const char *) final_line, '\n');
		if (ptr != NULL)
		{
			ft_strlcpy (buf, ptr + 1, BUFFER_SIZE + 1);
			*(ptr + 1) = '\0';
			return (final_line);
		}
	}
	return (final_line);
}

static char	*alt_buf(char *final_line, char buf[])
{
	char	*ptr;

	ptr = ft_strchr((const char *) final_line, '\n');
	if (ptr != NULL)
	{
		ft_strlcpy (buf, ptr + 1, BUFFER_SIZE + 1);
		*(ptr + 1) = '\0';
		return (buf);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	int			ret;
	static char	buf[1024][BUFFER_SIZE + 1];
	char		*final_line;

	final_line = get_first_buf(buf[fd], fd);
	if (!final_line)
		return (NULL);
	while (!ft_strchr((const char *) final_line, '\n'))
	{
		ret = read(fd, buf[fd], BUFFER_SIZE);
		if (ret == 0 && buf[fd][0] == '\0')
		{
			free (final_line);
			return (NULL);
		}
		buf[fd][ret] = '\0';
		if (ret == 0)
			return (final_line);
		final_line = get_fline(final_line, buf[fd]);
		if (!final_line)
			return (NULL);
		if (alt_buf(final_line, buf[fd]))
			return (final_line);
	}
	return (final_line);
}
/*
int	main(void)
{
	int		fd;
	int		i;
	char	*ptr;

	i = 0;
	fd = open("./files/41_with_nl", O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("open() failed\n", 1);
		return (1);
	}
	ptr = get_next_line(fd);
	while (ptr)
	{
		ft_putstr_fd(ptr, 1);
		free (ptr);
		ptr = get_next_line(fd);
	}
	if (close(fd) == -1)
	{
		ft_putstr_fd("close() failed\n", 1);
		return (1);
	}
	return (0);
}*/
