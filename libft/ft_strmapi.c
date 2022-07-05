/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:44:23 by daalmeid          #+#    #+#             */
/*   Updated: 2021/11/02 16:28:05 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>*/
#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	count;
	char			*ptr;

	if (s == 0)
		return (NULL);
	ptr = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!ptr)
		return (NULL);
	ptr[ft_strlen(s)] = '\0';
	count = 0;
	while (s[count] != '\0')
	{
		ptr[count] = f(count, s[count]);
		count++;
	}
	return (ptr);
}
/*
static char	toupper(unsigned int i, char c)
{
	i = 0;

	if (c >= 'a' && c <= 'z')
		return (c - 32);
	else
		return (c);
}

int	main(void)
{
	char const	*s1;
	char const	*s2;
	char		(*ptr_ft) (unsigned int, char);

	ptr_ft = &toupper;
	s1 = "Dario Almeida Barroca";
	s2 = ft_strmapi(s1, ptr_ft);
	printf("%s\n", s1);
	printf("%s\n", s2);
	return (0);
}
*/