/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:58:05 by daalmeid          #+#    #+#             */
/*   Updated: 2021/10/26 14:30:26 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <string.h>*/
#include <stdlib.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_size;

	i = 0;
	src_size = 0;
	while (src[src_size] != '\0')
		src_size++;
	if (dstsize == 0)
		return (src_size);
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_size);
}
/*
int	main(void)
{
	char	src[] = "good job";
	char	dst[] = " ";

	printf("%s, with source size: %lu\n", dst, ft_strlcpy(dst, src, 0));
	return (0);
}*/