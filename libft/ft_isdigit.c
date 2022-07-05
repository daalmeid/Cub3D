/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:57:15 by daalmeid          #+#    #+#             */
/*   Updated: 2021/10/21 17:00:43 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <ctype.h>
*/
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/*int	main(void)
{
	unsigned char	c = 'i';

	printf("%d\n", ft_isdigit(c));
	printf("%d\n", isdigit(c));
	return (0);
}
*/
