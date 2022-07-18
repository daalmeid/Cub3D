/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:15:19 by daalmeid          #+#    #+#             */
/*   Updated: 2021/10/25 20:01:34 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <string.h>
#include <stdio.h>*/
#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned const char	*ptr;

	i = 0;
	ptr = s;
	while (i < n)
	{
		if (ptr[i] == (unsigned char) c)
		{	
			ptr = &ptr[i];
			return ((void *) ptr);
		}
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	*str = "does it work?";

	printf("<%s>, pointer to <%s>\n", str, ft_memchr(str, 100 + 256, 3));
	printf("<%s>, pointer to <%s>\n", str, memchr(str, 100 + 256, 3));
	return (0);
}
*/