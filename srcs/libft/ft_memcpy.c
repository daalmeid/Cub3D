/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:49:29 by daalmeid          #+#    #+#             */
/*   Updated: 2021/11/02 16:21:06 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <string.h>
#include <stdio.h>*/
#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*ptr_dst;
	const char	*ptr_src;

	if (dst == 0 && src == 0)
		return (dst);
	i = 0;
	ptr_dst = dst;
	ptr_src = src;
	while (i < n)
	{
		ptr_dst[i] = ptr_src[i];
		i++;
	}
	return (dst);
}
/*
int	main(void)
{
	char	src[50];
	char	dst[50];

	strcpy(dst, "This is dst");
	puts(dst);
	memcpy(dst, src, 20);
	puts(dst);
	return (0);
}
*/