/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 19:28:01 by daalmeid          #+#    #+#             */
/*   Updated: 2021/11/02 16:25:58 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
/*#include <stdio.h>
*/
static char	*ft_alloc_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	while (s1[i] != '\0')
		i++;
	j = 0;
	while (s2[j] != '\0')
	{
		i++;
		j++;
	}
	ptr = malloc(sizeof(char) * (i + 1));
	if (!ptr)
		return (NULL);
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*ptr;
	unsigned int	i;
	unsigned int	j;

	if (s1 == 0 || s2 == 0)
		return (NULL);
	ptr = ft_alloc_strjoin(s1, s2);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}
/*
int	main(void)
{
	char const	*s1 = "Dario Al";
	char const	*s2 = "meida Barroca";

	printf("%s\n", s1);
	printf("%s\n", s2);
	printf("%s\n", ft_strjoin(s1, s2));
	free (ft_strjoin(s1, s2));
	return (0);
}
*/