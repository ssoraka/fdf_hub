/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lines_from_points.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:23:42 by ssoraka           #+#    #+#             */
/*   Updated: 2019/03/07 16:22:42 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./includes/ft_fdf.h"


int		ft_create_right_line(t_vektr *curr, t_vektr *next, t_line *line, t_arr *lines)
{
	if (next->abs.x == curr->abs.x + 1.0 && next->abs.y == curr->abs.y)
	{
		line->p1 = curr;
		line->p2 = next;
		if (!ft_arr_add(lines, (void *)line))
			return (FAIL);
	}
	return (SUCCESS);
}

int		ft_create_down_line(t_vektr *curr, t_vektr *down, t_line *line, t_arr *lines)
{
	if (down->abs.x == curr->abs.x && down->abs.y == curr->abs.y + 1.0)
	{
		line->p1 = curr;
		line->p2 = down;
		if (!ft_arr_add(lines, (void *)line))
			return (FAIL);
	}
	return (SUCCESS);
}

int		ft_create_lines_from_points(t_arr *points, t_arr *lines)
{
	t_vektr *curr;
	t_vektr *down;
	t_vektr *last;
	t_line line;

	ft_bzero8((void *)&line, sizeof(t_line));
	line.color = 0xFF00;
	last = ft_arr_get(points, points->elems_used - 1);
	down = ft_arr_get(points, 0);
	while ((curr = (t_vektr *)ft_arr_get_next(points)))
	{
		if (curr != last)
		{
			if (ft_create_right_line(curr, curr + 1, &line, lines) == FAIL)
				return (FAIL);
			while (down->abs.y <= curr->abs.y && down != last)
				down++;
			while (down->abs.y == curr->abs.y + 1 && down->abs.x < curr->abs.x && down != last)
				down++;
			if (ft_create_down_line(curr, down, &line, lines) == FAIL)
				return (FAIL);
		}
	}
	return(SUCCESS);
}