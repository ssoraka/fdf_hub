/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_active_points.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 20:59:39 by ssoraka           #+#    #+#             */
/*   Updated: 2019/04/19 13:13:30 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_fdf.h"

void	ft_print_point(t_pict *pic, t_vektr *v, int color)
{
	t_shape shape;

	ft_init_shape(&shape, CIRCLE, TRUE);
	shape.color = color;
	shape.len = 10;
	shape.print(pic, &v->zoom, &shape);
}

void	ft_print_line(t_pict *pic, t_vektr *v1, t_vektr *v2, int color)
{
	t_line line;

	line.color = color;
	line.index = DEFAULT_INDEX;
	line.p1 = v1;
	line.p2 = v2;
	draw_line_img(&line, pic, FALSE);
}

void	ft_print_active(t_pict *pic, t_param *param)
{
	if (param->centr)
		ft_print_point(pic, param->centr, ACTIVE_COLOR);
	if (param->p_new[0])
		ft_print_point(pic, param->p_new[0], CREATE_COLOR);
	if (param->p_new[1])
		ft_print_point(pic, param->p_new[1], CREATE_COLOR);
	if (param->p_new[2])
		ft_print_point(pic, param->p_new[2], CREATE_COLOR);
	if (param->p_new[0] && param->p_new[1])
		ft_print_line(pic, param->p_new[0], param->p_new[1], CREATE_COLOR);
	if (param->p_new[1] && param->p_new[2])
		ft_print_line(pic, param->p_new[1], param->p_new[2], CREATE_COLOR);
	if (param->p_new[0] && param->p_new[2])
		ft_print_line(pic, param->p_new[0], param->p_new[2], CREATE_COLOR);
}
