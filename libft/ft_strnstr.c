/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:36:41 by daalmeid          #+#    #+#             */
/*   Updated: 2021/10/26 18:20:29 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <string.h>*/
#include <stdlib.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t			i;
	size_t			j;
	const char		*ptr;

	i = 0;
	if (needle[0] == '\0')
		return ((char *) haystack);
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		while (haystack[i] == needle[j] && i < len)
		{
			if (needle[j + 1] == '\0')
			{	
				ptr = &haystack[i - j];
				return ((char *) ptr);
			}
			i++;
			j++;
		}
		if (j != 0)
			i = i - j;
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	*haystack = "this is my haystack";
	char	*needle = "hay";

	printf("haystack: %s --> first ocurrence of needle: %s\n",
	haystack, ft_strnstr(haystack, needle, 15));
	printf("haystack: %s --> first ocurrence of needle: %s\n",
	haystack, strnstr(haystack, needle, 15));
	return (0);
}
*/