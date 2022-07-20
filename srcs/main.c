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

void	prep_ptrs(t_mlx *mlx)
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
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!handle_new_image(&p->tex[i], p->mlx.ptr))
		{
			printf("Failed to load image\n");
			exit (2);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_app	p;
	char	*tmp;

	ft_memset(&p, 0, sizeof(t_app));
	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./prog *.cub\n", STDERR_FILENO);
		exit (1);
	}
	tmp = (argv[1]) + (ft_strlen(argv[1]) - 4);
	if (tmp <= argv[1] || ft_strncmp(tmp, ".cub", 5) != 0)
	{
		ft_putstr_fd("Error\nUnknown map file extension\n", STDERR_FILENO);
		exit(1);
	}
	readmap(&p, argv[1]);
	p.stat = true;
	prep_ptrs(&p.mlx);
	prep_tex_data(&p);
	hooks(&p);
	mlx_mouse_hide(p.mlx.ptr, p.mlx.win);
	mlx_mouse_move(p.mlx.ptr, p.mlx.win, MAP_W / 2, MAP_H / 2);
	mlx_loop(p.mlx.ptr);
	return (0);
}
