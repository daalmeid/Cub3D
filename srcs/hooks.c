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

static int	key_p(int key, t_app *p);
static int	key_r(int key, t_app *p);
static int	in_hook(t_app *p);
static int	out_hook(t_app *p);

void	hooks(t_app *p)
{
	mlx_hook(p->mlx.win, 9, 1L << 21, in_hook, p);
	mlx_hook(p->mlx.win, 10, 1L << 21, out_hook, p);
	mlx_hook(p->mlx.win, 2, 1L << 0, key_p, p);
	mlx_hook(p->mlx.win, 3, 1L << 1, key_r, p);
	mlx_loop_hook(p->mlx.ptr, handlers, p);
	mlx_hook(p->mlx.win, 17, 0, esc_handler, p);
}

static int	key_p(int key, t_app *p)
{
	if (key == KEY_M)
	{
		mlx_mouse_move(p->mlx.ptr, p->mlx.win, MAP_W / 2, MAP_H / 2);
		p->mouse_enable = !p->mouse_enable;
		return (0);
	}
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

static int	in_hook(t_app *p)
{
	if (p->mouse_enable)
	{
		mlx_mouse_hide(p->mlx.ptr, p->mlx.win);
		mlx_mouse_move(p->mlx.ptr, p->mlx.win, MAP_W / 2, MAP_H / 2);
	}
	p->in_window = true;
	return (0);
}

static int	out_hook(t_app *p)
{
	mlx_mouse_show(p->mlx.ptr, p->mlx.win);
	p->in_window = false;
	return (0);
}
