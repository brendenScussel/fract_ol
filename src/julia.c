/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 21:21:24 by bscussel          #+#    #+#             */
/*   Updated: 2020/01/10 21:42:52 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int					j_mouse(int x, int y, t_fractal *f)
{
	int				unused;
	int				y_location;
	double			z_offset;

	if (f->set == 1 && f->k.jp == 0)
	{
		unused = x;
		y_location = y - 450;
		z_offset = (1 / f->k.zoom) * 0.25;
		f->j_it = y_location * z_offset;
		julia_start(f);
	}
	return (0);
}

static int			julia_calc(t_fractal *f)
{
	double			x;
	double			y;
	double			xsq;
	double			ysq;

	x = (1.5 * (f->x - 400) / (200 * f->k.zoom) + f->k.x_shift);
	y = ((f->y - 300) / (WIN_V / 7 * f->k.zoom) + f->k.y_shift);
	xsq = x * x;
	ysq = y * y;
	f->i = 0;
	(f->i_max < 1) ? f->i_max = 1 : 0;
	while (xsq + ysq < 4 && f->i < f->i_max && f->j_it > -100 && f->j_it < 100)
	{
		f->c.zx = x;
		f->c.zy = y;
		f->c.zrsq = f->c.zx * f->c.zx;
		f->c.zisq = f->c.zy * f->c.zy;
		x = f->c.zrsq - f->c.zisq + f->c.cx + f->j_it * 0.004;
		y = 2 * f->c.zx * f->c.zy - f->c.cy + f->j_it * 0.004;
		xsq = x * x;
		ysq = y * y;
		f->i++;
	}
	return ((f->i == f->i_max) ? 0 : f->i * 255);
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
		res = julia_calc(f);
		if (f->e == 1)
			res = res << 8;
		else if (f->e == 2)
			res = res << 16;
		else if (f->e == 3 && res != 0)
			res += 16770816;
		i = f->x + (f->y * WIN_H);
		img[i] = (f->i % 3) ? res * f->q : res;
		f->x++;
	}
	return ((void *)f);
}

void				julia_start(t_fractal *f)
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
