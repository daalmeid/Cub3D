/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:44:45 by daalmeid          #+#    #+#             */
/*   Updated: 2021/10/29 12:10:23 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write (fd, "-2147483648", 11);
	else if (n < -9)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n / 10, fd);
		ft_putchar_fd(-n % 10 + '0', fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd(-n % 10 + '0', fd);
	}
	else if (n <= 9)
		ft_putchar_fd(n + '0', fd);
	else if (n > 9)
	{	
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
}
/*
int	main(void)
{
	int	n;
	int	fd;

	n = -2147483648;
	fd = 1;
	ft_putnbr_fd(n, fd);
	return (0);
}*/