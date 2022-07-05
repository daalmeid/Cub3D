/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:24:46 by daalmeid          #+#    #+#             */
/*   Updated: 2021/10/21 17:02:48 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <ctype.h>
*/
int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

/*int	main(void)
{
	unsigned char	c = 'f';

	printf("%d\n", ft_isprint(c));
	printf("%d\n", isprint(c));
	return (0);
}
*/
