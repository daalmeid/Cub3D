/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:57:06 by marvin            #+#    #+#             */
/*   Updated: 2022/07/18 16:57:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libc3d.h"

static int	esc_handler(t_app *p)
{
	mlx_destroy_image(p->mlx.ptr, p->mlx.data.ptr);
	mlx_destroy_window(p->mlx.ptr, p->mlx.win);
	exit(0);
	return (0);
}

static int	key_p(int key, t_app *p)
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

static int	key_r(int key, t_app *p)
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

static int	in_hook(t_app *app)
{
	(void)app;
	app->stat = true;
	return (0);
}


static int	out_hook(t_app *app)
{
	(void)app;
	app->stat = false;
	return (0);
}

void	hooks(t_app *p)
{
	mlx_hook(p->mlx.win, 10, 1L << 21, in_hook, p);
	mlx_hook(p->mlx.win, 9, 1L << 21, out_hook, p);
	mlx_hook(p->mlx.win, 2, 1L << 0, key_p, p);
	mlx_hook(p->mlx.win, 3, 1L << 1, key_r, p);
	mlx_loop_hook(p->mlx.ptr, handlers, p);
	mlx_hook(p->mlx.win, 17, 0, esc_handler, p);
}
