/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 22:11:47 by bscussel          #+#    #+#             */
/*   Updated: 2020/01/13 01:01:35 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void				sort_fractal(t_fractal *f)
{
	(f->i < 1) ? f->i = 1 : 0;
	mlx_clear_window(f->mlx, f->win);
	if (f->set == 0)
		err_prog(ERR_SORT);
	else if (f->set == 1)
		julia_start(f);
	else if (f->set == 2)
		mandel_start(f);
	else if (f->set == 3 || f->set == 4)
		gs_start(f);
}

void				struct_init(t_fractal *f)
{
	f->i = 0;
	f->i_max = 80;
	f->j_it = 0.025;
	f->q = 0;
	f->e = 0;
	f->c.cx = -0.8;
	f->c.cy = 0.15;
	f->c.zx = -0.8;
	f->c.zy = 0.15;
	f->k.zoom = 1.00;
	f->k.x_shift = -1.5;
	f->k.y_shift = -1;
	f->k.cnt = 0;
	f->k.jp = 1;
}

t_fractal			*ini_fractal(int set)
{
	t_fractal		*tmp;

	(!(tmp = (t_fractal *)malloc(sizeof(t_fractal))))
		? err_prog(ERR_MLX_INIT) : 0;
	(!(tmp->mlx = mlx_init())) ? err_prog(ERR_MLX_INIT) : 0;
	(!(tmp->win = mlx_new_window(tmp->mlx, WIN_H, WIN_V, "fract'ol")))
		? err_prog(ERR_WIN_INIT) : 0;
	(!(tmp->img = mlx_new_image(tmp->mlx, WIN_H, WIN_V)))
		? err_prog(ERR_WIN_INIT) : 0;
	tmp->data_addr = mlx_get_data_addr(tmp->img, &(tmp->bpp),
		&(tmp->s_l), &(tmp->endian));
	tmp->set = set;
	return (tmp);
}

int					fractol_get_set(char *arg)
{
	if (ft_strequ(arg, "julia") || ft_strequ(arg, "1"))
		return (1);
	else if (ft_strequ(arg, "mandelbrot") || ft_strequ(arg, "2"))
		return (2);
	else if (ft_strequ(arg, "sunspot") || ft_strequ(arg, "3"))
		return (3);
	else if (ft_strequ(arg, "gemini") || ft_strequ(arg, "4"))
		return (4);
	else
	{
		ft_printf("%s%s\nvalid sets:\n%s\n%s", BREAK, INVALID, SETS, BREAK);
		exit(1);
	}
}

int					main(int ac, char **av)
{
	unsigned int	set;
	t_fractal		*f;

	set = 0;
	if (ac == 2)
	{
		ft_printf("%s%s%s", INSTRUCTIONS, INSTRUCTION2, INSTRUCTION3);
		set = fractol_get_set(av[1]);
		f = ini_fractal(set);
		struct_init(f);
		sort_fractal(f);
		(f->set == 1) ? mlx_hook(f->win, 6, 1L < 6, j_mouse, f) : 0;
		mlx_key_hook(f->win, key_input, f);
		mlx_mouse_hook(f->win, mouse_input, f);
		mlx_loop(f->mlx);
	}
	else
		ft_printf("%s%s\nvalid sets:\n%s\n%s", BREAK, USAGE, SETS, BREAK);
	exit(0);
}
