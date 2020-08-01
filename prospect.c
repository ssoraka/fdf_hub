/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prospect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:54:52 by ssoraka           #+#    #+#             */
/*   Updated: 2019/10/27 17:54:52 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_fdf.h"

void	ft_sphere_perspective(t_param *param, t_point *p)
{
	long d;

	d = sqrt(p->x * p->x + p->y * p->y + param->radius * param->radius);
	if (param->perspective == SPHERE_M_PERSPECTIVE)
	{
		p->x = (param->radius * p->x) / d;
		p->y = (param->radius * p->y) / d;
	}
	else
	{
		p->x = (d * p->x) / param->radius;
		p->y = (d * p->y) / param->radius;
	}
}

void	ft_perspective(t_param *param, t_point *p, t_dpoint *rot_p, t_point *c)
{
	p->z = (int)(rot_p->z * param->len);
	if (p->z < param->radius - 60)
	{
		p->x = (int)(rot_p->x * param->len * param->radius
				/ (param->radius - p->z));
		p->y = (int)(rot_p->y * param->len * param->radius
				/ (param->radius - p->z));
		if (param->perspective == SPHERE_M_PERSPECTIVE
		|| param->perspective == SPHERE_P_PERSPECTIVE)
			ft_sphere_perspective(param, p);
		p->x += c->x;
		p->y += c->y;
	}
	else
	{
		p->x = UNPRINTABLE;
		p->y = UNPRINTABLE;
	}
	p->z += c->z;
}
