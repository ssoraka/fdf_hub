/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 20:59:39 by ssoraka           #+#    #+#             */
/*   Updated: 2019/04/19 13:13:30 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H

# include "../libft/libft.h"
# include "ft_buttons.h"

# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include "mlx.h"
# include "ft_fdf_struct.h"

# if defined(__linux__)
#  include "X11/X.h"
#  define KEY_PRESS_MASK KeyPressMask
#  define POINTER_MOTION_MASK PointerMotionMask
#  define BUTTON_PRESS_MASK ButtonPressMask
#  define BUTTON_RELEASE_MASK ButtonReleaseMask
#  define KEY_PRESS KeyPress
#  define KEY_RELEASE KeyRelease
#  define BUTTON_PRESS ButtonPress
#  define BUTTON_RELEASE ButtonRelease
#  define MOTION_NOTIFY MotionNotify
# else
#  define KEY_PRESS_MASK 0
#  define POINTER_MOTION_MASK 0
#  define BUTTON_PRESS_MASK 0
#  define BUTTON_RELEASE_MASK 0
#  define KEY_PRESS 		2
#  define KEY_RELEASE 		3
#  define BUTTON_PRESS 		4
#  define BUTTON_RELEASE 		5
#  define MOTION_NOTIFY 		6
# endif

# define ABS(nbr) ((nbr) >= 0 ? (nbr) : (-1) * (nbr))

/*
**	добавляем по 2 вершины между вершинами расчетной модели для сплайна
*/

# define COLOR_UP 0xFFFFFF
# define COLOR_DOWN 0x704214

# define DEFAULT_LINE_COLOR 0xFF00

# define BACKGROUND_COLOR 0x8F8F8F

# define WHITE_COLOR 0xFFFFFF
# define BLACK_COLOR 0x0
# define DEFAULT_COLOR -1
# define UNPRINTABLE -100

# define ZERO_COLOR 0xFF00
# define UP_COLOR 0xFF0000
# define DOWN_COLOR 0xFF

# define RED_COLOR 0xFF0000
# define GREEN_COLOR 0xFF00
# define BLUE_COLOR 0xFF
# define ACTIVE_COLOR RED_COLOR
# define CREATE_COLOR BLUE_COLOR

# define MSG_ERROR1 "Malloc error\0\0Not valid map\0File not found"

# define DELTA_Z 0.01
# define SPEED 10
# define ROTATE_ANGLE 0.05 / 180.0

/*
**	images
*/
# define CONST_LEN 100
# define CONST_RADIUS 1000
# define CONST_WIDTH 2000
# define CONST_HEINTH 1360
# define CAM_X (CONST_WIDTH / 2)
# define CAM_Y (CONST_HEINTH / 2)
# define RADIUS 3

# define DEFAULT_INDEX 0
# define MIN_INTEGER 0x80000000

typedef enum	e_persp
{
	NO_PERSPECTIVE,
	LINEAR_PERSPECTIVE,
	SPHERE_P_PERSPECTIVE,
	SPHERE_M_PERSPECTIVE,
	LAST_PERSPECTIVE
}				t_persp;

typedef enum	e_status
{
	NO_ERR = 0,
	MALLOC_ERROR,
	VALIDATION_ERROR,
	FILE_ERROR
}				t_stat;

typedef enum	e_form
{
	POINT,
	POINT_INDEX,
	RECTANGLE,
	CIRCLE
}				t_form;

/*
**	main.c
*/
void		ft_exit(t_all *all, char *error_message);

/*
**	prints.c
*/
void		ft_print_all_lines(t_arr *lines, t_pict *pic, t_param *param);
void		ft_print_all_poligons(t_arr *plgns, t_pict *pic, t_param *param);
void		ft_print_all_points(t_arr *points, t_pict *pic);
void		ft_rotate_all_points(t_arr *points, t_param *param);

/*
**	hooks.c
*/
int			ft_mouse_press(int button, int x, int y, void *parameters);
int			ft_mouse_release(int button, int x, int y, void *parameters);
int			ft_mouse_move(int x, int y, void *parameters);
int			ft_loop_hook(void *parameters);
void		ft_init_hooks(t_all *all);

/*
**	mouse.c
*/
int			ft_mouse_on_window(int x, int y);
int			ft_mouse_get_new_pos(int x, int y, t_param *param);
t_vektr		*ft_get_nearest_point(t_all *all, t_param *param);
void		ft_try_change_active_point(t_param *param, t_vektr *active);

/*
**	animation.c
*/
int			ft_move_camera(t_param *param);
int			ft_is_cam_moved(t_param *param);
int			ft_is_cam_rotated(t_param *param);
int			ft_auto_rotate(t_param *param);

/*
**	print_active_points.c
*/
void		ft_print_active(t_pict *pic, t_param *param);

/*
**	create_new_elem.c
*/
void		ft_add_point_for_creating(t_param *param, t_vektr *v);
void		ft_create_new_elem(t_all *all, t_param *param);

/*
**	create_lines_from_points.c
*/
int			ft_create_pair_from_points(t_arr *points, t_arr *lines);

/*
**	front.c
*/
void		ft_print_front(t_pict *pic, t_param *param);

/*
**	create_points_from_points.c
*/
t_stat		ft_get_color_from_string(char *str, int *color);
t_stat		ft_string_to_points(char *str, t_arr *points, int y);
t_stat		ft_points_from_file(char *name, t_arr *points);

/*
**	create_polygons_from_points.c
*/
int			ft_polygons_from_points(t_arr *points, t_arr *plgns);

/*
**	color_interpolation.c
*/
int			ft_interpolation(int percent, int color1, int color2, int byte);
int			ft_grad_color(int delta1, int delta2, int color1, int color2);
int			ft_set_color_to_point(t_line *line, t_point *p, int lower_45);
int			ft_int_interpolation(int y, int delta_y, int x1, int x2);

/*
**	print_shapes.c
*/
void		ft_init_shape(t_shape *shape, t_form form, t_bool is_particle);

/*
**	rotate.c
*/
void		ft_rotate_vek_around_vek_by_ang(t_dpoint *ox, t_dpoint *oy,
		double ang);
t_dpoint	ft_rot_dpoint(t_dpoint *v, t_oxyz *oxyz);
void		ft_rotate_point_around_point(t_param *param, t_vektr *p,
		t_dpoint *zero);
void		ft_rotate_xyz(t_oxyz *oxyz, t_dpoint *ang);

/*
**	prospect.c
*/
void		ft_sphere_perspective(t_param *param, t_point *p);
void		ft_perspective(t_param *param, t_point *p, t_dpoint *rot_p,
		t_point *c);

/*
**	images.c
*/
int			ft_create_img(t_pict *pic, void *mlx, int width, int height);
t_vis		*ft_create_mlx(int width, int heigth, char *name);
void		ft_destroy_img(t_pict *pic);
t_vis		*ft_destroy_mlx(t_vis **vis);

/*
**	picture.c
*/
void		ft_clear_image(t_pict *pic);
void		ft_save_image(t_pict *pic);
void		ft_return_image(t_pict *pic);

/*
**	lines_vektrs.c
*/
void		draw_line_img(t_line *line, t_pict *pic, int grad);

/*
**	polygons.c
*/
void		ft_print_plgn(t_plgn *plgn, t_pict *pic, int grad);
/*
**	polygons2.c
*/
void		ft_prepare_plgn_for_printing(t_plgn *plgn, t_param *param);
void		ft_draw_traing(t_pict *pic, t_vektr **p, int grad, int color);
void		ft_vektr_interpolation_by_y(t_vektr *p, t_vektr *p1, t_vektr *p2,
									int grad);
void		ft_swap_ptr(void **ptr1, void **ptr2);
void		ft_sort_points_by_y(t_vektr **p);
/*
**	keys.c
*/
int			ft_rotate_and_csale(t_param *param, int key);
int			ft_shift(t_param *vis, int key);
int			ft_deal_key(int key, void *parametrs);
int			ft_csale_picture(t_param *vis, int button, t_point *mouse);

/*
**	points.c
*/
void		ft_fill_point(t_point *p, int y, int x, int z);
void		ft_fill_dpoint(t_dpoint *p, t_real y, t_real x, t_real z);
t_real		ft_vekt_cos(t_dpoint a, t_dpoint b);
t_real		ft_dot_dpoints(t_dpoint *a, t_dpoint *b);
t_real		ft_vektr_len(t_dpoint *a);

/*
**	points2.c
*/
void		ft_create_xyz(t_oxyz *oxyz);
void		ft_normilize_vektor(t_dpoint *vek);
void		ft_get_perp_vekt_from_two(t_dpoint *answer, t_dpoint *a,
		t_dpoint *b);
void		ft_rotate_xyz_around_v(t_oxyz *oxyz, t_dpoint *v, double ang);
t_dpoint	ft_ret_norm(t_dpoint *a, t_dpoint *b, t_dpoint *c);

/*
**	get_pixel.c
*/
int			ft_get_nearest_id(t_pict *pic, t_point *pos);

#endif
