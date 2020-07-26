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

#include "./includes/ft_fdf.h"

void    ft_add_point_for_creating(t_param *param, t_vektr *v)
{
    if (param->id > 2)
        param->id = 0;
    param->p_new[param->id] = v;
    param->id++;
}

void    ft_create_lines(t_arr *lines, t_vektr *v1, t_vektr *v2)
{
    if (!v1 || !v2)
        return ;
    if (ft_arr_add(lines, (void *)v1))
    {
        if (!ft_arr_add(lines, (void *)v2))
            ft_del_elem(lines, lines->elems_used - 1);
    }
}

void    ft_create_new_elem(t_all *all, t_param *param)
{
    t_plgn plgn;
    t_line line;

    if (param->is_creating <= 1)
        return ;
    if (param->p_new[0] && param->p_new[1] && param->p_new[2])
    {
        plgn.p[0] = param->p_new[0];
        plgn.p[1] = param->p_new[1];
        plgn.p[2] = param->p_new[2];
        plgn.color = ZERO_COLOR;
        plgn.cos = 1.0;
        plgn.n = ft_ret_norm(&plgn.p[0]->abs, &plgn.p[1]->abs, &plgn.p[2]->abs);
        ft_arr_add(all->plgns, (void *)&plgn);
    }
    ft_create_lines(all->lines, param->p_new[0], param->p_new[1]);
    ft_create_lines(all->lines, param->p_new[0], param->p_new[2]);
    ft_create_lines(all->lines, param->p_new[1], param->p_new[2]);
    param->p_new[0] = NULL;
    param->p_new[1] = NULL;
    param->p_new[2] = NULL;
    param->id = 0;
    param->is_creating = 0;
}