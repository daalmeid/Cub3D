/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:20:42 by daalmeid          #+#    #+#             */
/*   Updated: 2021/11/02 16:00:24 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	count;
	size_t	dst_str_size;

	i = 0;
	count = 0;
	while (dst[count] != '\0' && count < dstsize)
		count++;
	dst_str_size = count;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && count < dstsize - 1)
	{
		dst[count] = src[i];
		i++;
		count++;
	}
	if (count < dstsize)
		dst[count] = '\0';
	i = ft_strlen(src);
	return (dst_str_size + i);
}
/*
int	main(void)
{
	char	dst[15];

	memset(dst, 'r', 6);
	printf("%s, with created string size: %lu\n", 
	dst, strlcat(dst, "lorem ipsum dolor sit amet", 15));
	return (0);
}*/