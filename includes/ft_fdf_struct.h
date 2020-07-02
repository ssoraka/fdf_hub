/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 20:59:39 by ssoraka           #+#    #+#             */
/*   Updated: 2019/04/19 13:13:30 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_STRUCT_H
# define FT_FDF_STRUCT_H


typedef double REAL;

typedef struct		s_point
{
	int y;
	int x;
	int z;
}					t_point;

typedef struct		s_dpoint
{
	REAL y;
	REAL x;
	REAL z;
}					t_dpoint;

typedef struct		s_vektr
{
	int color;
	struct s_dpoint	abs;
	struct s_point	zoom;
}					t_vektr;

typedef struct		s_line
{
	int color;
	struct s_point dir;
	struct s_point delta;
	struct s_vektr *p1;
	struct s_vektr *p2;
}					t_line;


typedef struct		s_plgn
{
	int color;
	struct s_vektr	*p[4];
	struct s_dpoint	n;
	struct s_dpoint	rot_n;
	REAL cos;
}					t_plgn;

typedef struct		s_pict
{
	void			*img;
	int				*addr;
	int				*index;
	int				*z_buffer;
	int				*addr_copy;
	int				*z_buffer_copy;
	int				cell;
	int				bits_per_pixel;
	int				size_line;
	int				count_line;
	int				count_byte;
	int				endian;
}					t_pict;


typedef struct		s_oxyz
{
	struct s_dpoint	oy;
	struct s_dpoint	ox;
	struct s_dpoint	oz;
}					t_oxyz;


typedef struct		s_param
{
	int				cam_x;
	int				cam_y;
	int				pause;
	int				exit;
	int				is_points_change;
	int				grad;
	double			len;
	struct s_dpoint	light;
	struct s_dpoint	ang;
	struct s_dpoint	cos;
	struct s_oxyz	oxyz;
}					t_param;


typedef struct		s_vis
{
	struct s_param	param;
	struct s_pict	pic;
	void			*mlx;
	void			*win;
}					t_vis;

typedef struct		s_all
{
	struct s_arr	*points;
	struct s_arr	*lines;
	struct s_vis	*vis;
}					t_all;


#endif
