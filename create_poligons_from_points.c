/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poligons.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:51:29 by ssoraka           #+#    #+#             */
/*   Updated: 2019/10/27 17:51:29 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_fdf.h"

int		ft_create_two_poligon(t_vektr *p1, t_vektr *p2, t_vektr *p3, t_arr *plgns)
{
    t_plgn plgn;

    if (p1 == p2 || p2 == p3 || p1 == p3)
        return (SUCCESS);
    if ((p1->abs.x + 1.0 == p2->abs.x && p1->abs.y == p2->abs.y
    && p1->abs.x == p3->abs.x && p1->abs.y + 1.0 == p3->abs.y)

    || (p3->abs.x == p1->abs.x + 1.0 && p3->abs.y == p1->abs.y
    && p3->abs.x == p2->abs.x && p3->abs.y == p2->abs.y + 1.0))
    {
        ft_bzero((void *) &plgn, sizeof(t_plgn));
        plgn.p[0] = p1;
        plgn.p[1] = p2;
        plgn.p[2] = p3;
        plgn.color = ZERO_COLOR;
        plgn.cos = 1.0;
        plgn.n = ft_ret_norm(&p1->abs, &p2->abs, &p3->abs);
        if (!ft_arr_add(plgns, (void *) &plgn))
            return (FAIL);
    }
    return (SUCCESS);
}

int		ft_poligons_from_points(t_arr *points, t_arr *plgns)
{
    t_vektr *curr;
    t_vektr *down;
    t_vektr *last;

    last = ft_arr_get(points, points->elems_used - 1);
    down = ft_arr_get(points, 0);
    while ((curr = (t_vektr *)ft_arr_get_next(points)))
    {
        if (curr == last || down == last)
            continue ;
        while (down->abs.y <= curr->abs.y && down != last)
            down++;
        while (down->abs.y == curr->abs.y + 1 && down->abs.x < curr->abs.x && down != last)
            down++;
        if (ft_create_two_poligon(curr, curr + 1, down, plgns) == FAIL)
            return (FAIL);
        if (down != last)
            if (ft_create_two_poligon(down, curr + 1, down + 1, plgns) == FAIL)
                return (FAIL);
    }
    return(SUCCESS);
}