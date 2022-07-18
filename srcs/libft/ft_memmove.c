/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:11:59 by daalmeid          #+#    #+#             */
/*   Updated: 2022/06/27 16:22:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <string.h>
#include <stdio.h>*/
#include <stdlib.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*ptr_dst;
	const char	*ptr_src;

	ptr_dst = dst;
	ptr_src = src;
	if (src < dst && src + len > dst)
	{	
		while (len > 0)
		{
			ptr_dst[len - 1] = ptr_src[len - 1];
			len--;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
/*
int	main(void)
{
	char	dest[] = "samestring is done";
	char	*src1 = &dest[4];
	char	*src2 = &dest[1];

	printf("Before memmove dest = %s, src = %s\n", src1, src2);
	ft_memmove(src1, src2, 17);
	printf("After memmove dest = %s, src = %s\n", src1, src2);
	return (0);
}
*/