/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:02:25 by daalmeid          #+#    #+#             */
/*   Updated: 2021/10/19 12:19:53 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <ctype.h>
*/
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	else
		return (c);
}
/*
int	main(void)
{
	unsigned char	c;

	c = 't';
	printf("%c -> %c\n", c, ft_toupper(c));
	c = 't';
	printf("%c -> %c\n", c, toupper(c));
	return (0);
}
*/