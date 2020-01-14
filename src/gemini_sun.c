/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gemini_sun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 00:56:37 by bscussel          #+#    #+#             */
/*   Updated: 2020/01/13 01:07:19 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

static int			gemini_calc(t_fractal *f)
{
	double			x;
	double			y;
	double			xcb;
	double			ycb;

	x = (1.5 * (f->x - 400) / (200 * f->k.zoom) + f->k.x_shift);
	y = ((f->y - 300) / (WIN_V / 7 * f->k.zoom) + f->k.y_shift);
	xcb = 0;
	ycb = 0;
	f->i = f->i_max;
	(f->i_max < 1) ? f->i_max = 1 : 0;
	while (xcb + ycb < 4 && f->i > 0)
	{
		f->c.zx = x * 2;
		f->c.zy = y * 2;
		f->c.zrsq = f->c.zx * f->c.zx;
		f->c.zisq = f->c.zy * f->c.zy;
		x = f->c.zrsq - f->c.zisq + f->c.cx;
		y = 2 * f->c.zx * f->c.zy + f->c.cy;
		xcb = x * x * x;
		ycb = y * y * y;
		f->i--;
	}
	return ((f->i == f->i_max) ? 0 : f->i * 200);
}

static int			sun_calc(t_fractal *f)
{
	double			x;
	double			y;
	double			xcb;
	double			ycb;

	x = (1.5 * (f->x - 400) / (200 * f->k.zoom) + f->k.x_shift);
	y = ((f->y - 300) / (WIN_V / 7 * f->k.zoom) + f->k.y_shift);
	xcb = 0;
	ycb = 0;
	f->i = f->i_max;
	(f->i_max < 1) ? f->i_max = 1 : 0;
	while (xcb + ycb < 4 && f->i > 0)
	{
		f->c.zx = x * 2;
		f->c.zy = y * 2;
		f->c.zrsq = f->c.zx * f->c.zx;
		f->c.zisq = f->c.zy * f->c.zy;
		x = f->c.zrsq - f->c.zisq;
		y = 2 * f->c.zx * f->c.zy;
		xcb = x * x * x;
		ycb = y * y * y;
		f->i--;
	}
	return ((f->i == f->i_max) ? 0 : f->i * 200);
}

static void			*scanlines(void *data)
{
	t_fractal		*f;
	int				*img;
	int				res;
	int				i;

	f = (t_fractal *)data;
	img = (int *)(f->data_addr);
	f->x = 5;
	while (f->x < WIN_H - 5)
	{
		res = (f->set == 3) ? sun_calc(f) : gemini_calc(f);
		if (f->e == 1 && res != 0)
			res = res << 8;
		else if (f->e == 2)
			res = res << 16;
		else if (f->e == 3 && res != 0)
			res += 14608394;
		(res == 0 && f->set == 3) ? res = 16773048 : 0;
		i = f->x + (f->y * WIN_H);
		img[i] = (f->i % 3) ? res * f->q : res;
		f->x++;
	}
	return ((void *)f);
}

void				gs_start(t_fractal *f)
{
	pthread_t		line[WIN_V];
	t_fractal		fd[WIN_V];
	int				i;

	ft_bzero(f->data_addr, WIN_V * WIN_H * (f->bpp / 8));
	f->y = 75;
	i = 0;
	while (f->y < WIN_V - 75)
	{
		ft_memcpy(&fd[i], f, sizeof(t_fractal));
		pthread_create(&(line[f->y]), NULL, scanlines, &(fd[i]));
		f->y++;
		i++;
	}
	while (f->y-- >= 0)
		pthread_join(line[f->y], NULL);
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}
