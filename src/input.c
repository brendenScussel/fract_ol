/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:59:46 by bscussel          #+#    #+#             */
/*   Updated: 2020/01/10 21:20:16 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

#include "../inc/fractol.h"

static void			color(int code, t_fractal *f)
{
	if (code == KEY_Q)
	{
		(f->q == 15) ? f->q = 3 : 0;
		f->q++;
		(f->q == 3) ? f->q = 15 : 0;
		(f->q == 4) ? f->q = 0 : 0;
	}
	else if (code == KEY_E)
	{
		f->e++;
		(f->e > 3) ? f->e = 0 : 0;
	}
}

static void			pan(int key, t_fractal *f)
{
	(key == KEY_W || key == KEY_UP) ?
		f->k.y_shift -= ((1 / f->k.zoom) * 0.25) : 0;
	(key == KEY_A || key == KEY_LFT) ?
		f->k.x_shift -= ((1 / f->k.zoom) * 0.25) : 0;
	(key == KEY_S || key == KEY_DWN) ?
		f->k.y_shift += ((1 / f->k.zoom) * 0.25) : 0;
	(key == KEY_D || key == KEY_RGH) ?
		f->k.x_shift += ((1 / f->k.zoom) * 0.25) : 0;
	sort_fractal(f);
}

void				frc_exit(t_fractal *f)
{
	mlx_destroy_window(f->mlx, f->win);
	free(f);
	f = NULL;
	ft_putendl("closing fract'ol...");
	exit(0);
}

int					key_input(int code, t_fractal *f)
{
	(code == KEY_ESC) ? frc_exit(f) : 0;
	(code == KEY_LFT || code == KEY_RGH || code == KEY_DWN || code == KEY_UP
		|| code == KEY_A || code == KEY_D || code == KEY_S || code == KEY_W)
		? pan(code, f) : 0;
	(code == KEY_Q || code == KEY_E) ? color(code, f) : 0;
	(code == NUM_MINS) ? f->i_max -= 10 : 0;
	(code == NUM_PLUS) ? f->i_max += 10 : 0;
	(code == KEY_MINS) ? f->i_max -= 1 : 0;
	(code == KEY_PLUS) ? f->i_max += 1 : 0;
	(code == KEY_COM) ? f->j_it += 0.25 : 0;
	(code == KEY_DOT) ? f->j_it -= 0.25 : 0;
	(code == NUM_0) ? struct_init(f) : 0;
	if (code == KEY_P && (f->set == 1 || f->set == 4))
		f->k.jp = (f->k.jp == 1) ? 0 : 1;
	sort_fractal(f);
	return (0);
}

int					mouse_input(int code, int x, int y, t_fractal *f)
{
	double			a;
	double			b;

	a = (2 * x - WIN_H) / (WIN_H * 0.5) / f->k.zoom;
	b = (2 * y - WIN_V) / (WIN_V * 0.5) / f->k.zoom;
	if (code == MOUSE_UP)
	{
		f->k.x_shift += a * 0.5;
		f->k.y_shift += b * 0.5;
		f->k.cnt++;
		f->k.zoom *= 1.25;
		(f->k.cnt > 0 && f->k.cnt % 5 == 0) ? f->i_max += 5 : 0;
	}
	else if (code == MOUSE_DWN)
	{
		f->k.x_shift -= a * 0.5;
		f->k.y_shift -= b * 0.5;
		f->k.cnt--;
		f->k.zoom *= 0.8;
		(f->k.cnt < 0 && f->k.cnt % 5 == 0) ? f->i_max -= 5 : 0;
	}
	sort_fractal(f);
	return (0);
}
