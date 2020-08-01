/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 18:28:19 by ssoraka           #+#    #+#             */
/*   Updated: 2019/10/27 18:28:20 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_fdf.h"

int		ft_mouse_on_window(int x, int y)
{
	if (x < 0 || y < 0 || x >= CONST_WIDTH || y >= CONST_HEINTH)
		return (FALSE);
	return (TRUE);
}

int		ft_mouse_get_new_pos(int x, int y, t_param *param)
{
	if (!ft_mouse_on_window(x, y))
	{
		param->mouse.x = -1;
		param->mouse.y = -1;
		param->right_button_press = FALSE;
		param->left_button_press = FALSE;
		return (FALSE);
	}
	param->mouse.x = x;
	param->mouse.y = y;
	return (TRUE);
}

t_vektr	*ft_get_nearest_point(t_all *all, t_param *param)
{
	int		id;
	t_vektr	*v;

	if (param->near_id == DEFAULT_INDEX)
		return (NULL);
	v = NULL;
	if (param->near_id > 0)
	{
		param->active_id = param->near_id;
		id = param->near_id - 1;
		v = (t_vektr *)ft_arr_get(all->points, id);
	}
	param->near_id = DEFAULT_INDEX;
	return (v);
}

void	ft_try_change_active_point(t_param *param, t_vektr *active)
{
	t_point old;

	if (!active)
		return ;
	old.x = param->centr->zoom.x;
	old.y = param->centr->zoom.y;
	param->centr = active;
	ft_rotate_point_around_point(param, param->centr, &param->centr->abs);
	param->cam_x += param->centr->zoom.x - old.x;
	param->cam_y += param->centr->zoom.y - old.y;
	param->target_x += param->centr->zoom.x - old.x;
	param->target_y += param->centr->zoom.y - old.y;
}
