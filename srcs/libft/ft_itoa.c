/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 19:18:55 by daalmeid          #+#    #+#             */
/*   Updated: 2021/10/25 19:00:05 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>*/
#include <stdlib.h>

static char	*alloc_nb(char *ptr, int n, int count)
{
	ptr[count] = '\0';
	count--;
	if (n == 0)
	{
		ptr[0] = '0';
		return (ptr);
	}
	while (n != 0)
	{
		if (n < 0)
		{
			ptr[0] = '-';
			ptr[count] = n % 10 * -1 + '0';
			n /= 10;
			n *= -1;
		}
		else
		{
			ptr[count] = n % 10 + '0';
			n /= 10;
		}	
		count--;
	}
	return (ptr);
}

char	*ft_itoa(int n)
{
	int		nb;
	int		count;
	char	*ptr;

	nb = n;
	count = 0;
	if (n == 0)
		count++;
	while (nb != 0)
	{
		nb /= 10;
		count++;
	}
	if (n < 0)
		count++;
	ptr = malloc(sizeof(char) * (count + 1));
	if (!ptr)
		return (NULL);
	return (alloc_nb(ptr, n, count));
}
/*
int	main(void)
{
	int	n;

	n = 2147483647;
	printf("%d\n", n);
	printf("%s\n", ft_itoa(n));
	return (0);
}
*/