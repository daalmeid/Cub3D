/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:45:14 by daalmeid          #+#    #+#             */
/*   Updated: 2021/10/22 18:06:51 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <string.h>
#include <stdio.h>*/
#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*ptr_b;

	i = 0;
	ptr_b = b;
	while (i < len)
	{	
		ptr_b[i] = c;
		i++;
	}
	return (b);
}
/*
int	main(void)
{
	char	str[50];

	strcpy(str, "This is string.h library function");
	puts(str);
	memset(str, '$', 7);
	puts(str);
	ft_memset(str, '&', 7);
	puts(str);
	return (0);
}
*/