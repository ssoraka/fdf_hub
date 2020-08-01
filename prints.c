/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:23:42 by ssoraka           #+#    #+#             */
/*   Updated: 2019/03/07 16:22:42 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_fdf.h"

void	ft_print_all_lines(t_arr *lines, t_pict *pic, t_param *param)
{
	t_line	line;
	t_vektr	**v;
	int		i;
	int		count;

	line.color = DEFAULT_LINE_COLOR;
	count = lines->elems_used / 2;
	v = (t_vektr **)lines->elems;
	i = 0;
	while (i < count)
	{
		line.index = DEFAULT_INDEX;
		line.p1 = *(v++);
		line.p2 = *(v++);
		draw_line_img(&line, pic, param->grad);
		i++;
	}
}

void	ft_print_all_poligons(t_arr *plgns, t_pict *pic, t_param *param)
{
	t_plgn	*plgn;
	int		i;
	int		count;

	count = plgns->elems_used;
	plgn = (t_plgn *)plgns->elems;
	i = 0;
	while (i < count)
	{
		ft_prepare_plgn_for_printing(plgn, param);
		ft_print_plgn(plgn, pic, param->grad);
		plgn++;
		i++;
	}
}

void	ft_print_all_points(t_arr *points, t_pict *pic)
{
	t_vektr	*v;
	int		i;
	int		count;
	t_shape	shape;

	ft_init_shape(&shape, POINT_INDEX, FALSE);
	count = points->elems_used;
	v = (t_vektr *)points->elems;
	i = 0;
	while (i < count)
	{
		shape.index = i + 1;
		shape.print(pic, &(v->zoom), &shape);
		v++;
		i++;
	}
}

void	ft_rotate_all_points(t_arr *points, t_param *param)
{
	t_vektr	*v;
	int		i;
	int		count;

	ft_rotate_point_around_point(param, param->centr, &param->centr->abs);
	param->centr->zoom.x = param->cam_x;
	param->centr->zoom.y = param->cam_y;
	count = points->elems_used;
	v = ft_arr_get(points, 0);
	i = 0;
	while (i < count)
	{
		ft_rotate_point_around_point(param, v + i, &param->centr->abs);
		i++;
	}
}
