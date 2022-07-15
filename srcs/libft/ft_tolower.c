/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:20:42 by daalmeid          #+#    #+#             */
/*   Updated: 2021/10/19 12:23:25 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <ctype.h>
*/
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	else
		return (c);
}
/*
int	main(void)
{
	unsigned char	c;

	c = 'T';
	printf("%c -> %c\n", c, ft_tolower(c));
	c = 'T';
	printf("%c -> %c\n", c, tolower(c));
	return (0);
}
*/