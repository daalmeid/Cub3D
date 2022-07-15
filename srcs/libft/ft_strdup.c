/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:51:43 by daalmeid          #+#    #+#             */
/*   Updated: 2021/10/21 17:35:29 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <string.h>
#include <stdio.h>
*/
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	int		i;
	char	*ptr;

	i = 0;
	while (s[i] != '\0')
		i++;
	ptr = malloc(sizeof(char) * (i + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
/*
int	main(void)
{
	char	*str = "daalmeid";

	printf("%s\n", str);
	printf("%s\n", ft_strdup(str));
	free (ft_strdup(str));
	return (0);
}
*/