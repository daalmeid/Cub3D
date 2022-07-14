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

#include "../headers/Cub3D.h"
#include "../headers/libft.h"
#include <stdio.h>

static void	esc_handler(t_player *p)
{
	mlx_destroy_image(p->mlx[0], p->mlx[2]);
	mlx_destroy_window(p->mlx[0], p->mlx[1]);
	exit(0);
}

static int	cross_handler(void *param)
{
	void	**mlx;

	mlx = (void **) param;
	mlx_destroy_image(mlx[0], mlx[2]);
	mlx_destroy_window(mlx[0], mlx[1]);
	exit(0);
}

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
	mlx_hook(p->mlx[1], 17, 0, cross_handler, p->mlx);
}

static void	prep_ptrs(void **mlx)
{
	int	tex_size;
	
	tex_size = 64;
	mlx[MLX_INIT] = mlx_init();
	if (!mlx[MLX_INIT])
	{
		perror("Error establishing connection to graphical system");
		exit(0);
	}
	mlx[MLX_WINDOW] = mlx_new_window(mlx[MLX_INIT], 800, 400, "Cub3D");
	if (!mlx[MLX_WINDOW])
	{
		perror("Error creating window");
		exit(0);
	}
	mlx[MLX_IMG_MAIN] = mlx_new_image(mlx[MLX_INIT], 800, 400);
	if (!mlx[MLX_IMG_MAIN])
	{
		perror("Error creating image");
		exit(0);
	}
	mlx[MlX_TEX_NO] =  mlx_xpm_file_to_image(mlx[MLX_INIT], "pics/mossy.xpm", &tex_size, &tex_size);
	if (!mlx[MlX_TEX_NO])
	{
		perror("Error creating image");
		exit(0);
	}
	mlx[MlX_TEX_SO] =  mlx_xpm_file_to_image(mlx[MLX_INIT], "pics/eagle.xpm", &tex_size, &tex_size);
	if (!mlx[MlX_TEX_SO])
	{
		perror("Error creating image");
		exit(0);
	}
	mlx[MlX_TEX_WE] =  mlx_xpm_file_to_image(mlx[MLX_INIT], "pics/purplestone.xpm", &tex_size, &tex_size);
	if (!mlx[MlX_TEX_WE])
	{
		perror("Error creating image");
		exit(0);
	}
	mlx[MlX_TEX_EA] =  mlx_xpm_file_to_image(mlx[MLX_INIT], "pics/redbrick.xpm", &tex_size, &tex_size);
	if (!mlx[MlX_TEX_EA])
	{
		perror("Error creating image");
		exit(0);
	}
}

void	prep_tex_data(t_player *p)
{
	p->tex_data[0] = handle_new_image(p->mlx[MlX_TEX_NO]);
	p->tex_data[1] = handle_new_image(p->mlx[MlX_TEX_SO]);
	p->tex_data[2] = handle_new_image(p->mlx[MlX_TEX_WE]);
	p->tex_data[3] = handle_new_image(p->mlx[MlX_TEX_EA]);

	p->map_data = handle_new_image(p->mlx[MLX_IMG_MAIN]);
}

int	main(void)
{
	t_player	p;
	int			world_map[24][24]=
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
	{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
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

	ft_memset(&p, 0, sizeof(p));
	p.pos_x = 22;
	p.pos_y = 12;
	p.dir_x = -1;
	p.dir_y = 0;
	prep_ptrs(p.mlx);
	prep_tex_data(&p);
	hooks(&p);
	p.cam_plane.dir_x = 0;
	p.cam_plane.dir_y = 0.66;
	raycaster(&p, world_map);
	ft_minimap(&p, world_map, 1, 1);
	mlx_put_image_to_window(p.mlx[0], p.mlx[1], p.mlx[2], 0, 0);
	mlx_mouse_get_pos(p.mlx[0], p.mlx[1], &p.mouse_x, &p.mouse_y);
	mlx_loop(p.mlx[0]);
}
