/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygons.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:51:29 by ssoraka           #+#    #+#             */
/*   Updated: 2019/10/27 17:51:29 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_fdf.h"

void	ft_save_points_colors(t_plgn *plgn, int *colors)
{
	colors[0] = plgn->p[0]->color;
	colors[1] = plgn->p[1]->color;
	colors[2] = plgn->p[2]->color;
	colors[3] = plgn->color;
}

void	ft_change_points_colors(t_plgn *plgn)
{
	plgn->p[0]->color = ft_grad_color((int)(1024 * plgn->cos),
			1024, plgn->p[0]->color, 0);
	plgn->p[1]->color = ft_grad_color((int)(1024 * plgn->cos),
			1024, plgn->p[1]->color, 0);
	plgn->p[2]->color = ft_grad_color((int)(1024 * plgn->cos),
			1024, plgn->p[2]->color, 0);
	plgn->color = ft_grad_color((int)(1024 * plgn->cos),
			1024, plgn->color, 0);
}

void	ft_recovery_points_colors(t_plgn *plgn, int *colors)
{
	plgn->p[0]->color = colors[0];
	plgn->p[1]->color = colors[1];
	plgn->p[2]->color = colors[2];
	plgn->color = colors[3];
}

int		ft_need_print_traing(t_vektr **p)
{
	if (p[0]->zoom.y < 0 && p[1]->zoom.y < 0 && p[2]->zoom.y < 0)
		return (FALSE);
	if (p[0]->zoom.x < 0 && p[1]->zoom.x < 0 && p[2]->zoom.x < 0)
		return (FALSE);
	if (p[0]->zoom.y >= CONST_HEINTH
		&& p[1]->zoom.y >= CONST_HEINTH
		&& p[2]->zoom.y >= CONST_HEINTH)
		return (FALSE);
	if (p[0]->zoom.x >= CONST_WIDTH
		&& p[1]->zoom.x >= CONST_WIDTH
		&& p[2]->zoom.x >= CONST_WIDTH)
		return (FALSE);
	if ((p[0]->zoom.y == UNPRINTABLE && p[0]->zoom.x == UNPRINTABLE)
		|| (p[1]->zoom.y == UNPRINTABLE && p[1]->zoom.x == UNPRINTABLE)
		|| (p[2]->zoom.y == UNPRINTABLE && p[2]->zoom.x == UNPRINTABLE))
		return (FALSE);
	return (TRUE);
}

void	ft_print_plgn(t_plgn *plgn, t_pict *pic, int grad)
{
	t_vektr	tmp;
	t_vektr	*p[4];
	int		colors[4];

	if (!ft_need_print_traing(plgn->p))
		return ;
	ft_save_points_colors(plgn, colors);
	ft_change_points_colors(plgn);
	p[0] = plgn->p[0];
	p[1] = plgn->p[1];
	p[2] = plgn->p[2];
	ft_sort_points_by_y(p);
	tmp.zoom.y = p[1]->zoom.y;
	ft_vektr_interpolation_by_y(&tmp, p[0], p[2], grad);
	p[3] = p[2];
	p[2] = &tmp;
	ft_draw_traing(pic, p, grad, plgn->color);
	p[0] = p[3];
	ft_draw_traing(pic, p, grad, plgn->color);
	ft_recovery_points_colors(plgn, colors);
}
