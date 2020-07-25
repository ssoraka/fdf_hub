/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 18:39:07 by ssoraka           #+#    #+#             */
/*   Updated: 2019/10/27 18:39:08 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_fdf.h"



int		ft_put_pixel_to_img(t_pict *pic, t_point *p, t_shape *shape)
{
    if (p->x < 0 || p->y < 0 || p->x >= CONST_WIDTH || p->y >= CONST_HEINTH)
        return (FALSE);
    if (pic->z_buffer[p->y * CONST_WIDTH + p->x] > p->z)
        return (FALSE);
    pic->index[p->y * CONST_WIDTH + p->x] = shape->index;
    if (shape->only_index)
        return (TRUE);
    pic->addr[p->y * CONST_WIDTH + p->x] = shape->color;
    pic->z_buffer[p->y * CONST_WIDTH + p->x] = p->z;
    return (TRUE);
}


//int		ft_put_pixel_to_img2(t_pict *pic, t_point *p, int color, int index)
//{
//    if (p->x < 0 || p->y < 0 || p->x >= CONST_WIDTH || p->y >= CONST_HEINTH)
//        return (FALSE);
//    if (pic->z_buffer[p->y * CONST_WIDTH + p->x] > p->z)
//        return (FALSE);
//    pic->addr[p->y * CONST_WIDTH + p->x] = color;
//    pic->z_buffer[p->y * CONST_WIDTH + p->x] = p->z;
//    pic->index[p->y * CONST_WIDTH + p->x] = index;
//    return (TRUE);
//}

int 	ft_print_rect(t_pict *pic, t_point *center, t_shape *shape)
{
	int i;
	int j;
	int shift;
	t_point p;

	j = 0;
	shift = - shape->len / 2;
	while (j <= shape->len)
	{
		i = 0;
		while (i <= shape->len)
		{
			ft_fill_point(&p, center->y + j + shift, center->x + i + shift, center->z);
			ft_put_pixel_to_img(pic, &p, shape);
			i++;
		}
		j++;
	}
	return (TRUE);
}


/* Вспомогательная функция, печатает точки, определяющие окружность */
void 	plot_circle(t_pict *pic, t_point *p, t_point *center, t_shape *shape)
{
	t_point point;

	ft_fill_point(&point, center->y + p->y, center->x + p->x, center->z);
	ft_put_pixel_to_img(pic, &point, shape);
	ft_fill_point(&point, center->y + p->y, center->x - p->x, center->z);
	ft_put_pixel_to_img(pic, &point, shape);
	ft_fill_point(&point, center->y - p->y, center->x + p->x, center->z);
	ft_put_pixel_to_img(pic, &point, shape);
	ft_fill_point(&point, center->y - p->y, center->x - p->x, center->z);
	ft_put_pixel_to_img(pic, &point, shape);
}

/* Вычерчивание окружности с использованием алгоритма Мичнера */
int 	circle(t_pict *pic, t_point *center, t_shape *shape)
{
	int x;
	int y;
	int delta;
	t_point p;

	x = 0;
	y = shape->len;
	delta = 3 - 2 * shape->len;
	while (x < y)
	{
		ft_fill_point(&p, x, y, 0);
		plot_circle(pic, &p, center, shape);
		ft_fill_point(&p, y, x, 0);
		plot_circle(pic, &p, center, shape);
		if (delta < 0)
			delta += 4 * x + 6;
		else
		{
			delta += 4 * (x - y) + 10;
			y--;
		}
		x++;
	}
	if (x == y)
		plot_circle(pic, &p, center, shape);
    return (TRUE);
}

void    ft_init_shape(t_shape *shape, t_form form)
{
    shape->only_index = FALSE;
    shape->form = form;
    if (form == POINT_INDEX)
        shape->only_index = TRUE;
    if (form == CIRCLE)
        shape->print = circle;
    else if (form == RECTANGLE)
        shape->print = ft_print_rect;
    else
        shape->print = ft_put_pixel_to_img;
}