/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 22:11:57 by bscussel          #+#    #+#             */
/*   Updated: 2020/01/13 01:02:28 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "../libft/lib/libft.h"
# include "../libft/ftpf/src/ft_printf.h"
# include "../minilibx/mlx.h"
# include "macros.h"
# include <math.h>
# include <pthread.h>

typedef struct			s_key
{
	double				zoom;
	double				x_shift;
	double				y_shift;
	int					cnt;
	int					jp;
}						t_key;

typedef struct			s_complex
{
	double				x_clc;
	double				y_clc;
	double				cx;
	double				cy;
	double				zx;
	double				zy;
	double				zrsq;
	double				zisq;
	double				crsq;
	double				cisq;
}						t_complex;

typedef struct			s_fractal
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*data_addr;
	int					bpp;
	int					s_l;
	int					endian;
	unsigned int		set;
	unsigned int		q;
	unsigned int		e;
	unsigned int		dot;
	int					x;
	int					y;
	int					i;
	int					i_max;
	double				j_it;
	t_key				k;
	t_complex			c;
}						t_fractal;

int						key_input(int key, t_fractal *param);
int						mouse_input(int code, int x, int y, t_fractal *param);
void					frc_exit(t_fractal *f);
void					sort_fractal(t_fractal *f);
void					struct_init(t_fractal *f);
void					mandel_start(t_fractal *f);
void					julia_start(t_fractal *f);
int						j_mouse(int x, int y, t_fractal *f);
void					gs_start(t_fractal *f);

#endif
