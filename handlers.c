/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:36:01 by marvin            #+#    #+#             */
/*   Updated: 2022/06/30 16:36:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/Cub3D.h"
#include "headers/libft.h"

int	handlers(int key, void *param)
{
	t_player *p;
	int worldMap[24][24]=
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	p = (t_player*)param;
	//printf("%d\n", key);
	if (key == 65307) //esc
	{	
		mlx_destroy_image(p->mlx[0], p->mlx[2]);
		mlx_destroy_window(p->mlx[0], p->mlx[1]);
		exit(0);
	}
	else if (key == 119) //W
	{
//		if (worldMap[(int) (p->posY)][(int)(p->posX + p->dirX)] == 0
//			&& worldMap[(int) (p->posY + p->dirY)][(int)(p->posX)] == 0)
		if (collider(p->posX + p->dirX / 2, p->posY + p->dirY / 2, worldMap) == true)
		{
			p->posX += (p->dirX / 2);
			p->posY += (p->dirY / 2);
			mlx_destroy_image(p->mlx[0], p->mlx[2]);
			p->mlx[2] = mlx_new_image(p->mlx[0], 800, 400);
			if (!p->mlx[2])
			{
				perror("Error creating image");
				exit(0);
			}
			raycaster(*p, worldMap);
			mlx_put_image_to_window(p->mlx[0], p->mlx[1], p->mlx[2], 0, 0);
		}
		else
			printf("collision north.\n");
	}
	else if (key == 115) //S
	{
//		if (worldMap[(int) (p->posY)][(int)(p->posX - p->dirX)] == 0
//			&& worldMap[(int) (p->posY - p->dirY)][(int)(p->posX)] == 0)
		if (collider(p->posX - p->dirX / 2, p->posY - p->dirY / 2, worldMap) == true)
		{
			p->posX -= (p->dirX / 2);
			p->posY -= (p->dirY / 2);
			mlx_destroy_image(p->mlx[0], p->mlx[2]);
			p->mlx[2] = mlx_new_image(p->mlx[0], 800, 400);
			if (!p->mlx[2])
			{
				perror("Error creating image");
				exit(0);
			}
			raycaster(*p, worldMap);
			mlx_put_image_to_window(p->mlx[0], p->mlx[1], p->mlx[2], 0, 0);
		}
		else
			printf("collision south.\n");
	}
	else if (key == 100) //D
	{
//		if (worldMap[(int) (p->posY)][(int)(p->posX - p->dirY)] == 0
//			&& worldMap[(int) (p->posY + p->dirX)][(int)(p->posX)] == 0)
		if (collider(p->posX - p->dirY / 2, p->posY + p->dirX / 2, worldMap) == true)
		{
			p->posX -= (p->dirY / 2);
			p->posY += (p->dirX / 2);
			mlx_destroy_image(p->mlx[0], p->mlx[2]);
			p->mlx[2] = mlx_new_image(p->mlx[0], 800, 400);
			if (!p->mlx[2])
			{
				perror("Error creating image");
				exit(0);
			}
			raycaster(*p, worldMap);
			mlx_put_image_to_window(p->mlx[0], p->mlx[1], p->mlx[2], 0, 0);
		}
		else
			printf("collision east.\n");
	}
	else if (key == 97) //A
	{
//		if (worldMap[(int) (p->posY)][(int)(p->posX + p->dirY)] == 0
//			&& worldMap[(int) (p->posY - p->dirX)][(int)(p->posX)] == 0)
		if (collider(p->posX + p->dirY / 2, p->posY - p->dirX / 2, worldMap) == true)
		{
			p->posX += (p->dirY / 2);
			p->posY -= (p->dirX / 2);
			mlx_destroy_image(p->mlx[0], p->mlx[2]);
			p->mlx[2] = mlx_new_image(p->mlx[0], 800, 400);
			if (!p->mlx[2])
			{
				perror("Error creating image");
				exit(0);
			}
			raycaster(*p, worldMap);
			mlx_put_image_to_window(p->mlx[0], p->mlx[1], p->mlx[2], 0, 0);
		}
		else
			printf("collision west.\n");
	}
	else if (key == 65363) //right arrow
	{
		double	theta = 0.05;
		double cs = cos(theta);
		double sn = sin(theta);

		double oldDir = p->dirX;
		p->dirX = p->dirX * cs - p->dirY * sn;
		p->dirY = oldDir * sn + p->dirY * cs;
		oldDir = p->camPlane.dirX;
		p->camPlane.dirX = p->camPlane.dirX * cs - p->camPlane.dirY * sn;
		p->camPlane.dirY = oldDir * sn + p->camPlane.dirY * cs;
		mlx_destroy_image(p->mlx[0], p->mlx[2]);
		p->mlx[2] = mlx_new_image(p->mlx[0], 800, 400);
		if (!p->mlx[2])
		{
			perror("Error creating image");
			exit(0);
		}
		raycaster(*p, worldMap);
		mlx_put_image_to_window(p->mlx[0], p->mlx[1], p->mlx[2], 0, 0);
	}
	else if (key == 65361) //left arrow
	{
		double	theta = -0.05;
		double cs = cos(theta);
		double sn = sin(theta);

		double oldDir = p->dirX;
		p->dirX = p->dirX * cs - p->dirY * sn;
		p->dirY = oldDir * sn + p->dirY * cs;
		oldDir = p->camPlane.dirX;
		p->camPlane.dirX = p->camPlane.dirX * cs - p->camPlane.dirY * sn;
		p->camPlane.dirY = oldDir * sn + p->camPlane.dirY * cs;
		mlx_destroy_image(p->mlx[0], p->mlx[2]);
		p->mlx[2] = mlx_new_image(p->mlx[0], 800, 400);
		if (!p->mlx[2])
		{
			perror("Error creating image");
			exit(0);
		}
		raycaster(*p, worldMap);
		mlx_put_image_to_window(p->mlx[0], p->mlx[1], p->mlx[2], 0, 0);
	}
	return (0);
}