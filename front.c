/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   front.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:51:29 by ssoraka           #+#    #+#             */
/*   Updated: 2019/10/27 17:51:29 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_fdf.h"

#define FRAME_X 200
#define FRAME_Y (CONST_HEINTH - 200)
#define FRAME_Z 0x7FFFFFFF
#define FRAME_LEN 100

void    ft_print_front(t_pict *pic, t_param *param)
{
    t_vektr v1;
    t_vektr v2;
    t_line line;

    line.index = DEFAULT_INDEX;
    line.p1 = &v1;
    line.p2 = &v2;
    ft_fill_point(&v1.zoom, FRAME_Y, FRAME_X, FRAME_Z);
    ft_fill_point(&v2.zoom, FRAME_Y + FRAME_LEN * param->oxyz.ox.y,
            FRAME_X + FRAME_LEN * param->oxyz.ox.x, FRAME_Z);
    line.color = RED_COLOR;
    draw_line_img(&line, pic, FALSE);
    ft_fill_point(&v2.zoom, FRAME_Y + FRAME_LEN * param->oxyz.oy.y,
                  FRAME_X + FRAME_LEN * param->oxyz.oy.x, FRAME_Z);
    line.color = GREEN_COLOR;
    draw_line_img(&line, pic, FALSE);
    ft_fill_point(&v2.zoom, FRAME_Y + FRAME_LEN * param->oxyz.oz.y,
                  FRAME_X + FRAME_LEN * param->oxyz.oz.x, FRAME_Z);
    line.color = BLUE_COLOR;
    draw_line_img(&line, pic, FALSE);
}
