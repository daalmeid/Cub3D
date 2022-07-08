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

static int	cross_handler(void *param)
{
	void	**mlx;

	mlx = (void **) param;
	mlx_destroy_image(mlx[0], mlx[2]);
	mlx_destroy_window(mlx[0], mlx[1]);
	exit(0);
}

static void	hooks(t_player *p)
{
	mlx_key_hook(p->mlx[1], handlers, p);
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

	p.pos_x = 22;
	p.pos_y = 12;
	p.dir_x = -1;
	p.dir_y = 0;
	prep_ptrs(p.mlx);
	prep_tex_data(&p);
	hooks(&p);
	p.cam_plane.dir_x = 0;
	p.cam_plane.dir_y = 0.66;
	raycaster(p, world_map);
	mlx_put_image_to_window(p.mlx[0], p.mlx[1], p.mlx[2], 0, 0);
	mlx_loop(p.mlx[0]);
}
