/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 19:47:19 by daalmeid          #+#    #+#             */
/*   Updated: 2021/11/02 16:48:06 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <string.h>*/
#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int			i;
	int			j;
	char		*ptr_mal;

	if (s1 == 0)
		return (NULL);
	while (ft_strchr(set, (int) *s1) != NULL && *s1 != '\0')
		s1++;
	j = ft_strlen(s1);
	while (ft_strchr(set, (int) s1[j - 1]) != NULL && j > 0)
		j--;
	ptr_mal = malloc(sizeof(char) * (j + 1));
	if (!ptr_mal)
		return (NULL);
	i = 0;
	while (i < j)
	{	
		ptr_mal[i] = s1[i];
		i++;
	}
	ptr_mal[i] = '\0';
	return (ptr_mal);
}
/*
int	main(void)
{
	char	*s1 = "   xxxtripouille";
	char	*set = " x";
	char	*s = ft_strtrim(s1, set);

	printf("%s\n", s1);
	printf("%s\n", s);
	printf("%d", strcmp(s, "tripouille"));
	free(ft_strtrim(s1, set));
	return (0);
}
*/