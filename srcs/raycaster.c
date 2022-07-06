/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 09:42:13 by marvin            #+#    #+#             */
/*   Updated: 2022/06/30 09:42:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Cub3D.h"
#include "../headers/libft.h"


void	raycaster(t_player p, int worldMap[24][24])
{
	t_data	img_data;
	img_data = handle_new_image(p.mlx);
	
	//printf("x: %f, int: %d\n", p.posX, (int)( p.posX - 0.1));
	//printf("y: %f\n", p.posY);
	for (int x = 0; x < mapWidth; x++)
	{
		double	cameraX = 2 * x/(double)mapWidth - 1;
		double	rayDirX = p.dirX + p.camPlane.dirX * cameraX;
		double	rayDirY = p.dirY + p.camPlane.dirY * cameraX;
		
		int	mapX = (int)p.posX;
		int	mapY = (int)p.posY;

		double sideDistX;
		double sideDistY;

		double deltaDistX;
		if (rayDirX != 0)
			deltaDistX = fabs(1 / rayDirX);
		else
			deltaDistX = 1e30;
		
		double deltaDistY;
		if (rayDirY != 0)
			deltaDistY = fabs(1 / rayDirY);
		else
			deltaDistY = 1e30;
		
		double perpWallDist;
	
		int stepX;
		int stepY;

		int hit = 0; 		//was there a wall hit?
		char side = '\0'; 			//was a NS or a EW wall hit?

		if (rayDirX < 0)
      	{
        	stepX = -1;
        	sideDistX = (p.posX - mapX) * deltaDistX;
      	}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - p.posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (p.posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - p.posY) * deltaDistY;
		}

		while (!hit)
		{
			if (sideDistX < sideDistY)
			{
				mapX += stepX;
				sideDistX += deltaDistX;
				side = 'y';
			}
			else
			{
				mapY += stepY;
				sideDistY += deltaDistY;
				side = 'x';
			}
			if (worldMap[mapY][mapX] == 1)
				hit = 1;
		}

		if (side == 'y')
			perpWallDist = sideDistX - deltaDistX;
		else
			perpWallDist = sideDistY - deltaDistY;
		
		int lineHeight = (int)(mapHeightPix / perpWallDist);

			//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + mapHeightPix / 2;
		if (drawStart < 0)
			drawStart = 0;

		int drawEnd = lineHeight / 2 + mapHeightPix / 2;
		if (drawEnd >= mapHeightPix)
			drawEnd = mapHeightPix - 1;

		int	color;
		if (side == 'y')
			color = 0xff0000;
		else
			color = 0x0000ff;
		
		int	ceiling = drawStart;
		while (ceiling != 0)
		{
			my_pixel_put(&img_data,  mapWidth - x - 1, ceiling--, 0x7f8059);
		}

		int	floor = drawEnd;
		while (floor < mapHeightPix)
		{
			my_pixel_put(&img_data,  mapWidth - x - 1, floor++, 0x414207);
		}
		while (drawStart <= drawEnd)
		{
			my_pixel_put(&img_data,  mapWidth - x - 1, drawStart++, color);
		}
	}
}