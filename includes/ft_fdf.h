/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mod1.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 20:59:39 by ssoraka           #+#    #+#             */
/*   Updated: 2019/04/19 13:13:30 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H


#include "../libft/libft.h"
#include "ft_buttons.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include "mlx.h"
#include "ft_fdf_struct.h"


#define ABS(nbr) ((nbr) >= 0 ? (nbr) : (-1) * (nbr))


/*
**	добавляем по 2 вершины между вершинами расчетной модели для сплайна
*/

#define COLOR_UP 0xFFFFFF
#define COLOR_DOWN 0x704214
//#define MAX_POINT 50

#define DEFAULT_LINE_COLOR 0xFF00

#define BACKGROUND_COLOR 0x8F8F8F

#define WHITE_COLOR 0xFFFFFF
#define BLACK_COLOR 0x0
#define DEFAULT_COLOR -1

#define ZERO_COLOR 0xFF00
#define UP_COLOR 0xFF0000
#define DOWN_COLOR 0xFF

#define RED_COLOR 0xFF0000
#define ACTIVE_COLOR RED_COLOR

#define MSG_ERROR1 "Malloc error\n"


#define SPEED 10
#define ROTATE_ANGLE 0.05 / 180.0

/*
**	images
*/
#define CONST_LEN 100
#define CONST_WIDTH 2000
#define CONST_HEINTH 1360
#define CAM_X (CONST_WIDTH / 2)
#define CAM_Y (CONST_HEINTH / 2)
//#define RADIUS (DELTA * CONST_LEN * 0.7)
#define RADIUS 3

#define DEFAULT_INDEX 0
#define MIN_INTEGER 0x80000000



typedef enum	e_persp
{
	NO_PERSPECTIVE,
	WATER2,
	MAGMA,
	MAGMA2,
	BLOB,
	OBSTCL,
	LAST_PERSPECTIVE
}				t_persp;

typedef enum	e_print
{
	COLOR = 1,
	RADIUS2,
	COLUMN_COUNT2
}				t_print;

typedef enum	e_column
{
	FLUID = 0,
	F_H,
	F_C,
	F_MASS,
	F_PRESS,
	F_DENS,
	F_VIS,
	F_Y_SPEED,
	COLUMN_COUNT
}				t_column;

typedef enum	e_form
{
	POINT,
	RECTANGLE,
	CIRCLE
}				t_form;



/*
**	main.c
*/
void	ft_exit(t_all *all, char *error_message);

/*
**	create_lines_from_points.c
*/
int		ft_create_pair_from_points(t_arr *points, t_arr *lines);

/*
**	create_points_from_points.c
*/
int		ft_get_color_from_string(char *str);
int		ft_string_to_points(char *str, t_arr *points, int y);
int		ft_points_from_file(char *name, t_arr *points);



/*
**	color_interpolation.c
*/
int		ft_interpolation(int percent, int color1, int color2, int byte);
int		ft_grad_color(int delta1, int delta2, int color1, int color2);
int		ft_set_color_to_point(t_line *line, t_point *p, int lower_45);
int		ft_int_interpolation(int y, int delta_y, int x1, int x2);

/*
**	print_shapes.c
*/
void    ft_init_shape(t_shape *shape, t_form form);

/*
**	rotate.c
*/
void	ft_rotate_xyz_around_xy(t_oxyz *oxyz, t_dpoint *ang);
void	ft_norm_vektor(t_dpoint *vek);
void	ft_rotate_vek_around_vek_by_ang(t_dpoint *ox, t_dpoint *oy, double ang);
void	ft_change_points(t_param *vis, t_vektr *p);
void	ft_rotate_xyz(t_oxyz *oxyz, t_dpoint *ang);
t_dpoint	ft_rot_dpoint(t_dpoint *v, t_oxyz *oxyz);
void	ft_ret_zoom_xyz(t_vektr *ox, t_param *vis);
void	ft_change_points5(t_param *param, t_vektr *p);
void	ft_rotate_point_around_point(t_param *param, t_vektr *p, t_dpoint *zero);

/*
**	images.c
*/
int		ft_create_img(t_pict *pic, void *mlx, int width, int heigth);
t_vis	*ft_create_mlx(int width, int heigth, char *name);
int		ft_not_need_print(t_line *line, t_pict *pic);

void	ft_destroy_img(t_pict *pic);
void	ft_clear_image(t_pict *pic);
void	ft_save_image(t_pict *pic);
void	ft_return_image(t_pict *pic);
t_vis	*ft_destroy_mlx(t_vis **vis);


/*
**	lines_vektrs.c
*/
void	draw_line_img(t_line *line, t_pict *pic, int grad);
// /*
// **	poligons.c
// */
// t_plgn	*ft_create_poligon(t_vektr *p1, t_vektr *p2, t_vektr *p3, int color);
// void	ft_del_poligines(t_plgn **begin);
// void	ft_swap_ptr(void **ptr1, void **ptr2);
// void	ft_sort_points_by_y(t_vektr **p);
// void	ft_vektr_interpolation_by_y(t_vektr *p, t_vektr *p1, t_vektr *p2, int grad);
// int		ft_need_print_traing(t_vektr **p, t_pict *pic);
// void	ft_draw_traing(t_pict *pic, t_vektr **p, int grad, int color);
// void	ft_print_plgn(t_plgn *plgn, t_pict *pic, int grad);
// void	ft_print_poligons(t_plgn *plgn, t_vektr *points, t_pict *pic, t_param *param);
// void	ft_prepare_plgn_for_printing(t_plgn *plgn, t_param *param);
/*
**	keys.c
*/
int		ft_rotate_and_csale(t_param *vis, int key);
int		ft_shift(t_param *vis, int key);
int		ft_deal_key(int key, void *parametrs);
int		ft_csale_picture(t_param *vis, int button, t_point *mouse);

/*
**	point.c
*/
void	ft_fill_point(t_point *p, int y, int x, int z);
void	ft_fill_dpoint(t_dpoint *p, REAL y, REAL x, REAL z);
void	ft_create_xyz(t_oxyz *oxyz);
void	ft_rotate_xyz_around_v(t_oxyz *oxyz, t_dpoint *v, double ang);
t_dpoint	ft_ret_norm(t_dpoint *a, t_dpoint *b, t_dpoint *c);
REAL	ft_vekt_cos(t_dpoint a, t_dpoint b);
REAL	ft_dot_dpoints(t_dpoint *a, t_dpoint *b);

/*
**	get_pixel.c
*/
int     ft_get_nearest_id(t_pict *pic, t_point *pos);

#endif
