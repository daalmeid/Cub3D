/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:11:12 by marvin            #+#    #+#             */
/*   Updated: 2022/07/19 18:15:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d_map.h"

/* Throw an error, call perror if syserr is true
	if code >= 0 exit else return */
int	werror(int code, char const *s, bool syserr)
{
	write(STDERR_FILENO, "Error\n", 6);
	if (syserr)
		perror(s);
	else if (s)
		write(STDERR_FILENO, s, ft_strlen(s));
	if (code >= 0)
		exit (code);
	return (code);
}

/* Throw an error if s, clear memory and exit */
int	map_error(int code, char const *s, t_mp *mp)
{
	if (s)
	{
		write(STDERR_FILENO, "Error\n", 6);
		if (mp->fd == -1)
			ft_putstr_fd((char *)s, STDERR_FILENO);
		else
		{
			ft_putstr_fd(mp->file, STDERR_FILENO);
			ft_putchar_fd(':', STDERR_FILENO);
			ft_putnbr_fd(mp->ln + 1, STDERR_FILENO);
			ft_putchar_fd(':', STDERR_FILENO);
			ft_putnbr_fd(mp->col + 1, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd((char *)s, STDERR_FILENO);
		}
	}
	else
		werror(-1, NULL, true);
	map_clean(mp->p, mp->fd, mp->line);
	exit (code);
}
