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

static int	esc_handler(t_player *p)
{
	mlx_destroy_image(p->mlx[0], p->map_data.ptr);
	mlx_destroy_window(p->mlx[0], p->mlx[1]);
	exit(0);
	return (0);
}
/*
static int	cross_handler(t_player *p)
{;
	mlx_destroy_image(p->mlx[0], p->map_data.ptr);
	mlx_destroy_window(p->mlx[0], p->mlx[1]);
	exit(0);
}
*/
static int key_p(int key, t_player *p)
{
	if (key == KEY_ESC)
		esc_handler(p);
	else if (key == KEY_W)
		p->wasd[0] = 1;
	else if (key == KEY_S)
		p->wasd[2] = 1;
	else if (key == KEY_D)
		p->wasd[3] = 1;
	else if (key == KEY_A)
		p->wasd[1] = 1;
	else if (key == KEY_RGT_ARR)
		p->wasd[5] = 1;
	else if (key == KEY_LFT_ARR)
		p->wasd[4] = 1;
	return (0);
}

static int key_r(int key, t_player *p)
{
	if (key == KEY_W)
		p->wasd[0] = 0;
	else if (key == KEY_S)
		p->wasd[2] = 0;
	else if (key == KEY_D)
		p->wasd[3] = 0;
	else if (key == KEY_A)
		p->wasd[1] = 0;
	else if (key == KEY_RGT_ARR)
		p->wasd[5] = 0;
	else if (key == KEY_LFT_ARR)
		p->wasd[4] = 0;
	return (0);
}

static void	hooks(t_player *p)
{
	mlx_hook(p->mlx[1], 2, 1L<<0, key_p, p);
	mlx_hook(p->mlx[1], 3, 1L<<1, key_r, p);
	mlx_loop_hook(p->mlx[0], handlers, p);
	mlx_hook(p->mlx[1], 17, 0, esc_handler, p->mlx);
}

static void	prep_ptrs(void **mlx)
{	
	mlx[MLX_INIT] = mlx_init();
	if (!mlx[MLX_INIT])
	{
		perror("Error establishing connection to graphical system");
		exit(0);
	}
	mlx[MLX_WINDOW] = mlx_new_window(mlx[MLX_INIT], map_width, map_height, "Cub3D");
	if (!mlx[MLX_WINDOW])
	{
		perror("Error creating window");
		exit(0);
	}
	/*
	mlx[MLX_IMG_MAIN] = mlx_new_image(mlx[MLX_INIT], 800, 400);
	if (!mlx[MLX_IMG_MAIN])
	{
		perror("Error creating image");
		exit(0);
	}	mlx[MlX_TEX_NO] =  mlx_xpm_file_to_image(mlx[MLX_INIT], "content/mossy.xpm", &tex_size, &tex_size);
	if (!mlx[MlX_TEX_NO])
	{
		perror("Error creating image");
		exit(0);
	}
	mlx[MlX_TEX_SO] =  mlx_xpm_file_to_image(mlx[MLX_INIT], "content/eagle.xpm", &tex_size, &tex_size);
	if (!mlx[MlX_TEX_SO])
	{
		perror("Error creating image");
		exit(0);
	}
	mlx[MlX_TEX_WE] =  mlx_xpm_file_to_image(mlx[MLX_INIT], "content/purplestone.xpm", &tex_size, &tex_size);
	if (!mlx[MlX_TEX_WE])
	{
		perror("Error creating image");
		exit(0);
	}
	mlx[MlX_TEX_EA] =  mlx_xpm_file_to_image(mlx[MLX_INIT], "content/redbrick.xpm", &tex_size, &tex_size);
	if (!mlx[MlX_TEX_EA])
	{
		perror("Error creating image");
		exit(0);
	}
	*/
}

void	prep_tex_data(t_player *p)
{
	if (!handle_new_image(&p->tex[0], p->mlx[0], "content/mossy.xpm"))
	{
		printf("Failed to load image\n");
		exit (2);
	}
	if (!handle_new_image(&p->tex[1], p->mlx[0], "content/eagle.xpm"))
	{
		printf("Failed to load image\n");
		exit (2);
	}
	if (!handle_new_image(&p->tex[2], p->mlx[0], "content/purplestone.xpm"))
	{
		printf("Failed to load image\n");
		exit (2);
	}
	if (!handle_new_image(&p->tex[3], p->mlx[0], "content/redbrick.xpm"))
	{
		printf("Failed to load image\n");
		exit (2);
	}

	p->map_data.width = map_width;
	p->map_data.height = map_height;
	p->map_data.ptr = mlx_new_image(p->mlx[0], map_width, map_height);
	p->map_data.addr = mlx_get_data_addr(p->map_data.ptr, &p->map_data.bpp,
			&p->map_data.line_length, &p->map_data.endian);
}

int	main(void)
{
	t_player	p;

	ft_memset(&p, 0, sizeof(p));
	p.pos.x = 22;
	p.pos.y = 12;
	p.dir.x = -1;
	p.dir.y = 0;
	p.plane.x = 0;
	p.plane.y = 0.66;

	prep_ptrs(p.mlx);
	prep_tex_data(&p);
	hooks(&p);
	mlx_mouse_get_pos(p.mlx[0], p.mlx[1], &p.mouse.x, &p.mouse.y);
	mlx_loop(p.mlx[0]);
}
