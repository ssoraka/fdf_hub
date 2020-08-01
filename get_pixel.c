/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 18:28:19 by ssoraka           #+#    #+#             */
/*   Updated: 2019/10/27 18:28:20 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_fdf.h"

#define SEARCH_RADIUS 15

int		ft_get_index(t_pict *pic, int x, int y)
{
	if (x < 0 || y < 0 || x >= CONST_WIDTH || y >= CONST_HEINTH)
		return (DEFAULT_INDEX);
	return (pic->index[y * CONST_WIDTH + x]);
}

int		ft_get_id_from_rect(t_pict *pic, t_point *p, int rad)
{
	int i;

	i = -1;
	while (++i <= rad * 2)
	{
		if (ft_get_index(pic, p->x - rad + i, p->y + rad) > DEFAULT_INDEX)
			return (ft_get_index(pic, p->x - rad + i, p->y + rad));
		if (ft_get_index(pic, p->x - rad + i, p->y - rad) > DEFAULT_INDEX)
			return (ft_get_index(pic, p->x - rad + i, p->y - rad));
	}
	i = 0;
	while (++i < rad * 2)
	{
		if (ft_get_index(pic, p->x + rad, p->y - rad + i) > DEFAULT_INDEX)
			return (ft_get_index(pic, p->x + rad, p->y - rad + i));
		if (ft_get_index(pic, p->x - rad, p->y - rad + i) > DEFAULT_INDEX)
			return (ft_get_index(pic, p->x - rad, p->y - rad + i));
	}
	return (DEFAULT_INDEX);
}

int		ft_get_nearest_id(t_pict *pic, t_point *pos)
{
	t_point	p;
	int		i;
	int		index;

	ft_fill_point(&p, pos->y, pos->x, 0);
	index = DEFAULT_INDEX;
	i = -1;
	while (++i <= SEARCH_RADIUS && index == DEFAULT_INDEX)
		index = ft_get_id_from_rect(pic, &p, i);
	return (index);
}
