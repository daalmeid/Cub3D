/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:04:21 by marvin            #+#    #+#             */
/*   Updated: 2022/06/28 16:04:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/Cub3D.h"
#include "headers/libft.h"
#include <stdio.h>

int	cross_handler(void *param)
{
	void	**mlx;

	mlx = (void **) param;
	mlx_destroy_image(mlx[0], mlx[2]);
	mlx_destroy_window(mlx[0], mlx[1]);
	exit(0);
}

static int	esc_handler(int key, void **mlx, int *x, int *y)
{
	(void)x;
	(void)y;

	printf("%d\n", key);
	if (key == 65307)
	{	
		mlx_destroy_image(mlx[0], mlx[2]);
		mlx_destroy_window(mlx[0], mlx[1]);
		exit(0);
	}
	return (0);
}

static void	hooks(void **mlx)
{
	mlx_key_hook(mlx[1], esc_handler, mlx);
	mlx_hook(mlx[1], 17, 0, cross_handler, mlx);
}

int	main(void)
{
	void	*mlx[3];
	
	mlx[0] = mlx_init();
	if (!mlx[0])
	{
		perror("Error establishing connection to graphical system");
		exit(0);
	}
	mlx[1] = mlx_new_window(mlx[0], 800, 400, "Cub3D");
	if (!mlx[1])
	{
		perror("Error creating window");
		exit(0);
	}
	mlx[2] = mlx_new_image(mlx[0], 700, 300);
	if (!mlx[2])
	{
		perror("Error creating image");
		exit(0);
	}
	hooks(mlx);
	
	t_data	img_data;

	img_data = handle_new_image(mlx);
	int i = 0;
	int adder = 0x000100;
	int color = 0xff0000;
	while (i < 700)
	{
		int j = 0;
		color += adder;
		if (color == 0xffff00)
			adder = -0x010000;
		else if (color == 0x00ff00)
			adder = 0x000001;
		else if (color == 0x00ffff)
			adder = -0x000100;
		else if (color == 0x0000ff)
			adder = 0x010000;
		else if (color == 0xff00ff)
			adder = -0x000001;
		else if (color == 0xff0000)
			adder = 0x000100;
		while (j < 300)
		{
			my_pixel_put(&img_data, i, j, color);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx[0], mlx[1], mlx[2], 50, 50);
	mlx_loop(mlx[0]);
}