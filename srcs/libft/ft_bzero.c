/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:15:04 by daalmeid          #+#    #+#             */
/*   Updated: 2021/10/25 12:37:16 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <string.h>
#include <stdio.h>*/
#include <stdlib.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = s;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
	return ;
}
/*
int	main(void)
{
	char	str_bzero[50];
	char	str_ft_bzero[50];

	printf("string with bzero:");
	strcpy(str_bzero, "This line should disappear");
	puts(str_bzero);
	bzero(str_bzero, 6);
	printf("string with bzero:");
	puts(str_bzero);
	printf("string with ft_bzero:");
	strcpy(str_ft_bzero, "This line should disappear too");
	puts(str_ft_bzero);
	ft_bzero(str_ft_bzero, 6);
	printf("string with ft_bzero:");
	puts(str_ft_bzero);
	return (0);
}
*/