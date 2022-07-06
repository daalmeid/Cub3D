/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 12:00:34 by marvin            #+#    #+#             */
/*   Updated: 2022/07/01 12:00:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Cub3D.h"
#include "../headers/libft.h"

bool	collider(double posX, double posY, int worldMap[24][24])
{
		double	theta = 0.05;

		double	vX = 0.2;
		double	vY = 0;

		if (worldMap[(int)(posY + vY)][(int)(posX + vX)] == 1)
			return false;
		while (theta < 6.25) //~360 degrees in radians
		{
			double cs = cos(theta);
			double sn = sin(theta);
			double oldDir = vX;
			vX = vX * cs - vY * sn;
			vY = oldDir * sn + vY * cs;
			if (worldMap[(int)(posY + vY)][(int)(posX + vX)] == 1)
				return false;
			theta += 0.05;
		}
		return (true);
}