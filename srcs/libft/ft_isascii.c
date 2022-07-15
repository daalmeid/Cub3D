/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:19:43 by daalmeid          #+#    #+#             */
/*   Updated: 2021/10/21 17:02:07 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <ctype.h>
*/
int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

/*int	main(void)
{
	unsigned char	c = 'i';

	printf("%d\n", ft_isascii(c));
	printf("%d\n", isascii(c));
	return (0);
}
*/
