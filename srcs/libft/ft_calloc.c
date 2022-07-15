/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:32:12 by daalmeid          #+#    #+#             */
/*   Updated: 2022/06/27 16:22:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>*/
#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	*ptr;

	ptr = malloc(size * count);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size * count);
	return (ptr);
}
/*
int	main(void)
{
	int	*ptr_calloc;
	int	*ptr_ft_calloc;
	int	i_calloc;

	i_calloc = 0;
	ptr_calloc = calloc(6, sizeof(int));
	ptr_ft_calloc = ft_calloc(6, sizeof(int));
	while (i_calloc < 6)
	{	
		printf("   calloc[%d] == %d; ", i_calloc, ptr_calloc[i_calloc]);
		i_calloc++;
	}
	printf("\n");
	i_calloc = 0;
	while (i_calloc < 6)
	{
		printf("ft_calloc[%d] == %d; ", i_calloc, ptr_ft_calloc[i_calloc]);
		i_calloc++;
	}
	printf("\n\n");
	free(ptr_calloc);
	free(ptr_ft_calloc);
	return (0);
}
*/