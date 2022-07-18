/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.00.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 000/06/08 16:00:01 by marvin            #+#    #+#             */
/*   Updated: 000/06/08 16:00:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libc3d.h"

static void	prep_ptrs(t_mlx *mlx)
{	
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
	{
		perror("Error establishing connection to graphical system");
		exit(0);
	}
	mlx->win = mlx_new_window(mlx->ptr, MAP_W, MAP_H, "Cub3D");
	if (!mlx->win)
	{
		perror("Error creating window");
		exit(0);
	}
	mlx->data.ptr = mlx_new_image(mlx->ptr, MAP_W, MAP_H);
	if (!mlx->data.ptr)
	{
		perror("Error creating image");
		exit(0);
	}
	mlx->data.addr = mlx_get_data_addr(mlx->data.ptr, &mlx->data.bpp,
			&mlx->data.line_length, &mlx->data.endian);
	mlx->data.width = MAP_W;
	mlx->data.height = MAP_H;
}

void	prep_tex_data(t_app *p)
{
	p->tex[0].path = "content/mossy.xpm";
	if (!handle_new_image(&p->tex[0], p->mlx.ptr))
	{
		printf("Failed to load image\n");
		exit (2);
	}
	p->tex[1].path = "content/eagle.xpm";
	if (!handle_new_image(&p->tex[1], p->mlx.ptr))
	{
		printf("Failed to load image\n");
		exit (2);
	}
	p->tex[2].path = "content/purplestone.xpm";
	if (!handle_new_image(&p->tex[2], p->mlx.ptr))
	{
		printf("Failed to load image\n");
		exit (2);
	}
	p->tex[3].path = "content/redbrick.xpm";
	if (!handle_new_image(&p->tex[3], p->mlx.ptr))
	{
		printf("Failed to load image\n");
		exit (2);
	}
}

int	main(void)
{
	t_app	p;

	ft_memset(&p, 0, sizeof(p));
	p.pos.x = 22;
	p.pos.y = 12;
	p.dir.x = -1;
	p.dir.y = 0;
	p.plane.x = 0;
	p.plane.y = 0.66;
	prep_ptrs(&p.mlx);
	prep_tex_data(&p);
	hooks(&p);
	mlx_mouse_get_pos(p.mlx.ptr, p.mlx.win, &p.mouse.x, &p.mouse.y);
	mlx_loop(p.mlx.ptr);
}
