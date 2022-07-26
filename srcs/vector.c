/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:11:18 by rafernan          #+#    #+#             */
/*   Updated: 2022/07/25 16:11:19 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libc3d.h"

t_v2d	v2d(double x, double y)
{
	t_v2d	tmp;

	tmp.x = x;
	tmp.y = y;
	return (tmp);
}

t_v2i	v2i(int x, int y)
{
	t_v2i	tmp;

	tmp.x = x;
	tmp.y = y;
	return (tmp);
}
