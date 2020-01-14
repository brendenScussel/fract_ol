/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 15:25:07 by bscussel          #+#    #+#             */
/*   Updated: 2020/01/09 23:24:18 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

/*
**	this equation, overall, could be condensed. However, doing so would
**	sacrifice what little extra speed that can be achieved this way.
**	There is a slight preformance benifit from NOT conducting math operations
**	from within another operation. Likewise, calling pow() would be simple,
**	but jumping between functions adds extra processing time.
*/

int					mandel_calc(t_fractal *f)
{
	double			x;
	double			y;

	f->c.cx = 0.00;
	f->c.cy = 0.00;
	x = (double)(1.5 * (f->x - 400) / (200 * f->k.zoom) + f->k.x_shift);
	y = (double)((f->y - 300) / (WIN_V / 7 * f->k.zoom) + f->k.y_shift);
	f->c.crsq = 0.00;
	f->c.cisq = 0.00;
	f->i = 0;
	while (f->c.crsq + f->c.cisq < 4 && f->i < f->i_max)
	{
		f->c.zx = f->c.cx;
		f->c.zy = f->c.cy;
		f->c.zrsq = f->c.zx * f->c.zx;
		f->c.zisq = f->c.zy * f->c.zy;
		f->c.cx = (f->c.zrsq) - (f->c.zisq) + x;
		f->c.cy = 2 * (f->c.zx * f->c.zy) + y;
		f->c.crsq = f->c.cx * f->c.cx;
		f->c.cisq = f->c.cy * f->c.cy;
		f->i++;
	}
	return ((f->i == f->i_max) ? 0 : f->i * 255);
}

/*
**	10 lines are removed from the horizontal resolution for the same reasons
**		as in mandel_start()
**	if the int f->e is 1 or 2, the color will be shifted from
**		blue to green to red.
*/

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
		res = mandel_calc(f);
		if (f->e == 1)
			res = res << 8;
		else if (f->e == 2)
			res = res << 16;
		else if (f->e == 3 && res != 0)
			res += 7869157;
		i = f->x + (f->y * WIN_H);
		img[i] = (f->i % 3) ? res * f->q : res;
		f->x++;
	}
	return ((void *)f);
}

/*
**	data_address is set to 0 when ever a new image is made
**	a total of 150 lines are subtracted from the verticle resolution
**		soley for preformance. IE: less to draw.
**	an equal amount of copies of t_fractal are created for each thread
*/

void				mandel_start(t_fractal *f)
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
