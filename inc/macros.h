/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 15:48:41 by bscussel          #+#    #+#             */
/*   Updated: 2020/01/13 01:03:18 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define MAX_INT 2147483647
# define MIN_INT -2147483648
# define WIN_H 1200
# define WIN_V 900

/*
**  keys
*/

# define KEY_A 0
# define KEY_D 2
# define KEY_E 14
# define KEY_H 4
# define KEY_Q 12
# define KEY_S 1
# define KEY_W 13
# define KEY_P 35
# define KEY_COM 43
# define KEY_DOT 47
# define KEY_0 29
# define KEY_1 18
# define KEY_2 19
# define KEY_3 20
# define KEY_4 21
# define KEY_5 23
# define KEY_6 22
# define NUM_0 82
# define NUM_1 83
# define NUM_2 84
# define NUM_3 85
# define NUM_4 86
# define NUM_5 87
# define NUM_6 88
# define KEY_PLUS 24
# define KEY_MINS 27
# define NUM_PLUS 69
# define NUM_MINS 78
# define KEY_LFT 123
# define KEY_RGH 124
# define KEY_DWN 125
# define KEY_UP 126
# define KEY_ESC 53

/*
**  keys
*/

# define MOUSE_LFT	1
# define MOUSE_RGH	2
# define MOUSE_MID	3
# define MOUSE_UP	4
# define MOUSE_DWN	5

/*
**  messeges
*/

# define BREAK			"===============\n"
# define USAGE			"usage: ./fractol {fractal set}"
# define SETS			"{julia} - {mandelblot} - {sunspot} - {gemini}"
# define INVALID		"Error: arguement not recognized"
# define ERR_MLX_INIT	"Error: mlx pointer could not initialize"
# define ERR_WIN_INIT	"Error: window pointer could not initialize"
# define ERR_IMG_INIT	"Error: image pointer could not initialize"
# define ERR_SORT		"A sorting error has occurred"
# define INSTRUCTIONS	"\nARROWS/WASD:\tpan\nQ:\t\tcolor blend\nE:\t\t"
# define INSTRUCTION2	"spectrum\nPLUS/MIN:\titterate\nMOUSE:\t\tzoom\n"
# define INSTRUCTION3	"P:\t\titteration {julia}\n#O:\t\treset\n\n"

#endif
