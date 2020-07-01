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


#define WHITE_COLOR 0xFFFFFF
#define BLACK_COLOR 0x0
#define OBSTACLES_TOP_COLOR 0x704214
#define OBSTACLES_FRONT_COLOR 0x5b432d

#define OBSTACLES_RIGHT_COLOR 0x654321

#define MSG_ERROR1 "Malloc error\n"




/*
**	images
*/
#define CONST_WIDTH 2000
#define CONST_HEINTH 1360
#define CAM_X 1200
#define CAM_Y 1100
//#define RADIUS (DELTA * CONST_LEN * 0.7)
#define RADIUS 3






typedef enum	e_fluids
{
	//EMPTY = 0,
	WATER = 1,
	WATER2,
	MAGMA,
	MAGMA2,
	BLOB,
	OBSTCL,
	FLUIDS
}				t_fluids;

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

typedef enum	e_rain
{
	RAIN_FALSE,
	NEED_STOP_PRINT_FOR_RAIN,
	RAIN_ACTIVATE,
}				t_rain;



/*
**	main.c
*/


/*
** initialization.c
*/

// void	ft_init_delta_xyz(void);
// void	ft_del_all(char *message);


// /*
// **	color_interpolation.c
// */
// int		ft_interpolation(int percent, int color1, int color2, int byte);
// int		ft_grad_color(int delta1, int delta2, int color1, int color2);
// int		ft_set_color_to_point(t_line *line, t_point *p, int lower_45);
// int		ft_int_interpolation(int y, int delta_y, int x1, int x2);

// /*
// **	print_shapes.c
// */
// void	ft_print_rect2(t_pict *pic, t_point *center, int len, int color);
// void	plot_circle2(t_pict *pic, t_point *p, t_point *center, int color_code);
// void	circle2(t_pict *pic, t_vektr *center, int radius, int color_code);

// /*
// **	rotate.c
// */
// void	ft_norm_vektor(t_dpoint *vek);
// void	ft_rotate_vek_around_vek_by_ang(t_dpoint *ox, t_dpoint *oy, double ang);
// void	ft_change_points4(t_param *vis, t_vektr *p);
// void	ft_rotate_xyz(t_oxyz *oxyz, t_dpoint *ang);
// t_dpoint	ft_rot_dpoint(t_dpoint *v, t_oxyz *oxyz);
// void	ft_ret_zoom_xyz(t_vektr *ox, t_param *vis);
// void	ft_change_points5(t_param *param, t_vektr *p);

// /*
// **	images.c
// */
// int		ft_create_img(t_pict *pic, void *mlx, int width, int heigth);
// t_vis	*ft_create_mlx(int width, int heigth, char *name);
// int		ft_not_need_print(t_line *line, t_pict *pic);
// int		ft_put_pixel_to_img2(t_pict *pic, t_point *p, int color);
// int		ft_put_pixel_to_img(t_pict *pic, t_point *p, int color);
// void	ft_destroy_img(t_pict *pic);
// void	ft_clear_image(t_pict *pic);
// void	ft_save_image(t_pict *pic);
// void	ft_return_image(t_pict *pic);
// t_vis	*ft_destroy_mlx(t_vis **vis);


// /*
// **	lines_vektrs.c
// */
// t_vektr	*ft_new_vektor2(REAL x, REAL y, REAL z, int color);
// t_vektr	*ft_add_vektor2(void *ptr, t_point *p, int color);
// t_line	*ft_new_line(t_vektr *p1, t_vektr *p2, int color);
// void	ft_add_line(t_line **begin, t_vektr *p1, t_vektr *p2, int color);
// void	ft_del_vektor(t_vektr **begin);
// void	ft_del_lines(t_line **begin);
// void	draw_line_img_lower_452(t_line *line, t_point *p, t_pict *pic, int grad);
// void	draw_line_img_over_452(t_line *line, t_point *p, t_pict *pic, int grad);
// void	draw_line_img2(t_line *line, t_pict *pic, int grad);
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
// /*
// **	keys.c
// */
// int		ft_rotate_and_csale(t_param *vis, int key);
// int		ft_shift(t_param *vis, int key);
// int		deal_key(int key, void *param);

/*
**	point.c
*/
void	ft_fill_point(t_point *p, int y, int x, int z);
void	ft_fill_dpoint(t_dpoint *p, REAL y, REAL x, REAL z);
void	ft_create_xyz(t_oxyz *oxyz);
t_dpoint	ft_ret_norm(t_dpoint *a, t_dpoint *b, t_dpoint *c);
REAL	ft_vekt_cos(t_dpoint a, t_dpoint b);
REAL	ft_dot_dpoints(t_dpoint *a, t_dpoint *b);



#endif
