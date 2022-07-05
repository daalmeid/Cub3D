/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 18:37:59 by daalmeid          #+#    #+#             */
/*   Updated: 2021/11/02 16:24:08 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
/*#include <stdio.h>
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (s == 0)
		return (NULL);
	if (ft_strlen(s) + 1 < len)
		ptr = malloc(sizeof(char) * ft_strlen(s) + 1);
	else
		ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (i < len && s[start + i] != '\0' && start < ft_strlen(s))
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
/*
int	main(void)
{
	char	*str = "this is the string to substring";

	printf("%s\n", str);
	printf("%s\n", ft_substr(str, 10, 20));
	free (ft_substr(str, 10, 20));
	return (0);
}
*/