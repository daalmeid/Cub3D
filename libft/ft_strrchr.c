/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:47:19 by daalmeid          #+#    #+#             */
/*   Updated: 2021/10/26 13:43:01 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <string.h>
#include <stdio.h>*/
#include <stdlib.h>

char	*ft_strrchr(const char *s, int c)
{
	int			i;
	const char	*ptr;

	i = 0;
	while (s[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (s[i] == (char) c)
		{
			ptr = &s[i];
			return ((char *) ptr);
		}
		i--;
	}
	return (NULL);
}
/*
int	main(void)
{
	const char	*str = "does it work?";

	printf("<%s>, pointer to <%s>\n", str, ft_strrchr(str, 'o'));
	printf("<%s>, pointer to <%s>\n", str, strrchr(str, 'o'));
	return (0);
}
*/