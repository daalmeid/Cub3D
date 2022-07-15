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

#include "../includes/libc3d.h"

static int	esc_handler(t_app *p)
{
	mlx_destroy_image(p->mlx.ptr, p->mlx.data.ptr);
	mlx_destroy_window(p->mlx.ptr, p->mlx.win);
	exit(0);
	return (0);
}
/*
static int	cross_handler(t_app *p)
{;
	mlx_destroy_image(p->mlx.ptr, p->mlx.data.ptr);
	mlx_destroy_window(p->mlx.ptr, p->mlx.win);
	exit(0);
}
*/
static int key_p(int key, t_app *p)
{
	if (key == KEY_ESC)
		esc_handler(p);
	else if (key == KEY_W)
		p->kmap[_W] = true;
	else if (key == KEY_S)
		p->kmap[_S] = true;
	else if (key == KEY_D)
		p->kmap[_D] = true;
	else if (key == KEY_A)
		p->kmap[_A] = true;
	else if (key == KEY_RGT_ARR)
		p->kmap[_RA] = true;
	else if (key == KEY_LFT_ARR)
		p->kmap[_LA] = true;
	return (0);
}

static int key_r(int key, t_app *p)
{
	if (key == KEY_W)
		p->kmap[_W] = false;
	else if (key == KEY_S)
		p->kmap[_S] = false;
	else if (key == KEY_D)
		p->kmap[_D] = false;
	else if (key == KEY_A)
		p->kmap[_A] = false;
	else if (key == KEY_RGT_ARR)
		p->kmap[_RA] = false;
	else if (key == KEY_LFT_ARR)
		p->kmap[_LA] = false;
	return (0);
}

static void	hooks(t_app *p)
{
	mlx_hook(p->mlx.win, 2, 1L<<0, key_p, p);
	mlx_hook(p->mlx.win, 3, 1L<<1, key_r, p);
	mlx_loop_hook(p->mlx.ptr, handlers, p);
	mlx_hook(p->mlx.win, 17, 0, esc_handler, p);
}

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
