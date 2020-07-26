/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:54:52 by ssoraka           #+#    #+#             */
/*   Updated: 2019/10/27 17:54:52 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_fdf.h"

/*
**	избавление от погрешности
*/

void	ft_rotate_vek_around_vek_by_ang(t_dpoint *ox, t_dpoint *oy, double ang)
{
	double cosa;
	double sina;
	double temp_x;
	double temp_y;
	double temp_z;

	if (ang == 0.0 || !ox || !oy)
		return ;
	cosa = cos(ang);
	sina = sin(ang);
	temp_x = ox->x * (cosa + (1 - cosa) * oy->x * oy->x);
	temp_x = temp_x + ox->y * ((1 - cosa) * oy->x * oy->y - sina * oy->z);
	temp_x = temp_x + ox->z * ((1 - cosa) * oy->x * oy->z + sina * oy->y);
	temp_y = ox->x * ((1 - cosa) * oy->y * oy->x + sina * oy->z);
	temp_y = temp_y + ox->y * (cosa + (1 - cosa) * oy->y * oy->y);
	temp_y = temp_y + ox->z * ((1 - cosa) * oy->y * oy->z - sina * oy->x);
	temp_z = ox->x * ((1 - cosa) * oy->z * oy->x - sina * oy->y);
	temp_z = temp_z + ox->y * ((1 - cosa) * oy->z * oy->y + sina * oy->x);
	temp_z = temp_z + ox->z * (cosa + (1 - cosa) * oy->z * oy->z);
	ox->x = temp_x;
	ox->y = temp_y;
	ox->z = temp_z;
	ft_normilize_vektor(ox);
}



t_dpoint	ft_rot_dpoint(t_dpoint *v, t_oxyz *oxyz)
{
	t_dpoint rot_v;
	t_dpoint *ox;
	t_dpoint *oy;
	t_dpoint *oz;

	ox = &(oxyz->ox);
	oy = &(oxyz->oy);
	oz = &(oxyz->oz);
	rot_v.x = (ox->x * v->x + oy->x * v->y + oz->x * v->z);
	rot_v.y = (ox->y * v->x + oy->y * v->y + oz->y * v->z);
	rot_v.z = (ox->z * v->x + oy->z * v->y + oz->z * v->z);
	return (rot_v);
}

void	ft_change_points(t_param *param, t_vektr *p)
{
	t_dpoint rot_p;

	rot_p = ft_rot_dpoint(&p->abs, &param->oxyz);
	p->zoom.x = (int)(rot_p.x * param->len) + param->cam_x;
	p->zoom.y = (int)(rot_p.y * param->len) + param->cam_y;
	p->zoom.z = (int)(rot_p.z * param->len);
}


void    ft_linear_perspective(t_param *param, t_point *p, t_dpoint *rot_p)
{
    p->z = (int)(rot_p->z * param->len);

    if (p->z < param->radius - 100)
    {
        p->x = (int)(rot_p->x * param->len * param->radius/(param->radius - p->z)) + param->centr->zoom.x;
        p->y = (int)(rot_p->y * param->len * param->radius/(param->radius - p->z)) + param->centr->zoom.y;
    }
    else
    {
        p->x = -1;
        p->y = -1;
    }
    p->z += param->centr->zoom.z;
}

void    ft_sphere_perspective(t_param *param, t_point *p, t_dpoint *rot_p)
{
    long d;
    t_point tmp;

    tmp.x = (int)(rot_p->x * param->len);
    tmp.y = (int)(rot_p->y * param->len);
    tmp.z = (int)(rot_p->z * param->len);

    d = sqrt(tmp.x * tmp.x + tmp.y * tmp.y + param->radius * param->radius);

    if (param->perspective == SPHERE_M_PERSPECTIVE)
    {
        p->x = (param->radius * tmp.x) / d + param->centr->zoom.x;
        p->y = (param->radius * tmp.y) / d + param->centr->zoom.x;
    }
    else
    {
        p->x = (d * tmp.x) / param->radius + param->centr->zoom.x;
        p->y = (d * tmp.y) / param->radius + param->centr->zoom.x;
    }
    p->z = (int)(rot_p->z * param->len) + param->centr->zoom.z;

}

void	ft_rotate_point_around_point(t_param *param, t_vektr *p, t_dpoint *zero)
{
	t_dpoint rot_p;

	ft_fill_dpoint(&rot_p, p->abs.y - zero->y, p->abs.x - zero->x, p->abs.z - zero->z);
	rot_p = ft_rot_dpoint(&rot_p, &param->oxyz);

	if (param->perspective == LINEAR_PERSPECTIVE)
        ft_linear_perspective(param, &p->zoom, &rot_p);
//    else if (param->perspective == SPHERE_M_PERSPECTIVE || param->perspective == SPHERE_P_PERSPECTIVE)
//        ft_sphere_perspective(param, &p->zoom, &rot_p);
    else
    {
        p->zoom.x = (int)(rot_p.x * param->len) + param->centr->zoom.x;
        p->zoom.y = (int)(rot_p.y * param->len) + param->centr->zoom.y;
        p->zoom.z = (int)(rot_p.z * param->len) + param->centr->zoom.z;
    }
}


void	ft_rotate_xyz(t_oxyz *oxyz, t_dpoint *ang)
{
    if (ang->z != 0)
    {
        ft_rotate_vek_around_vek_by_ang(&(oxyz->oy), &(oxyz->oz), ang->z);
        ft_rotate_vek_around_vek_by_ang(&(oxyz->ox), &(oxyz->oz), ang->z);
    }
    if (ang->x != 0)
    {
        ft_rotate_vek_around_vek_by_ang(&(oxyz->oy), &(oxyz->ox), ang->x);
        ft_rotate_vek_around_vek_by_ang(&(oxyz->oz), &(oxyz->ox), ang->x);
    }
    if (ang->y != 0)
    {
        ft_rotate_vek_around_vek_by_ang(&(oxyz->ox), &(oxyz->oy), ang->y);
        ft_rotate_vek_around_vek_by_ang(&(oxyz->oz), &(oxyz->oy), ang->y);
    }
    ft_fill_dpoint(ang, 0.0, 0.0, 0.0);
   // ft_get_perp_vekt_from_two(&(oxyz->oz), &(oxyz->ox), &(oxyz->oy));
   // ft_get_perp_vekt_from_two(&(oxyz->oy), &(oxyz->oz), &(oxyz->ox));
}