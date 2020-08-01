/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 18:28:19 by ssoraka           #+#    #+#             */
/*   Updated: 2019/10/27 18:28:20 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_fdf.h"

int		ft_mouse_press(int button, int x, int y, void *parameters)
{
	t_all	*all;
	t_param	*param;
	t_vektr	*active;

	all = (t_all *)parameters;
	param = &all->vis->param;
	if (param->exit || !ft_mouse_on_window(x, y))
		return (0);
	if (ft_csale_picture(param, button, &param->mouse))
		param->is_points_change = TRUE;
	if (button == RIGHT_BUTTON)
		if ((active = ft_get_nearest_point(all, param)))
		{
			if (param->is_creating)
				ft_add_point_for_creating(param, active);
			else
				ft_try_change_active_point(param, active);
			param->is_points_change = TRUE;
		}
	return (0);
}

int		ft_mouse_release(int button, int x, int y, void *parameters)
{
	t_all	*all;
	t_param	*param;

	all = (t_all *)parameters;
	param = &all->vis->param;
	if (param->exit || !ft_mouse_on_window(x, y))
		return (0);
	if (button == MIDDLE_BUTTON)
		param->right_button_press = FALSE;
	else if (button == LEFT_BUTTON)
		param->left_button_press = FALSE;
	return (0);
}

int		ft_mouse_move(int x, int y, void *parameters)
{
	t_all	*all;
	t_param	*param;

	all = (t_all *)parameters;
	param = &all->vis->param;
	param->near_id = DEFAULT_INDEX;
	if (param->exit || !ft_mouse_get_new_pos(x, y, param))
		return (0);
	param->near_id = ft_get_nearest_id(&all->vis->pic, &param->mouse);
	if (ft_is_cam_moved(param))
		param->is_points_change = TRUE;
	if (ft_is_cam_rotated(param))
		param->is_points_change = TRUE;
	return (0);
}

int		ft_loop_hook(void *parameters)
{
	t_all *all;
	t_vis *vis;

	all = (t_all *)parameters;
	vis = all->vis;
	if (vis->param.exit)
		ft_exit(all, NULL);
	if ((ft_move_camera(&vis->param) + ft_auto_rotate(&vis->param)))
		vis->param.is_points_change = TRUE;
	ft_create_new_elem(all, &vis->param);
	if (vis->param.is_points_change)
	{
		ft_clear_image(&(vis->pic));
		ft_rotate_all_points(all->points, &(vis->param));
		if (vis->param.is_poligons_need_print)
			ft_print_all_poligons(all->plgns, &(vis->pic), &(vis->param));
		else
			ft_print_all_lines(all->lines, &(vis->pic), &(vis->param));
		ft_print_all_points(all->points, &(vis->pic));
		ft_print_active(&(vis->pic), &(vis->param));
		ft_print_front(&(vis->pic), &(vis->param));
	}
	mlx_put_image_to_window(vis->mlx, vis->win, vis->pic.img, 0, 0);
	mlx_do_sync(all->vis->mlx);
	return (0);
}

void	ft_init_hooks(t_all *all)
{
	void *param;
	void *win;

	param = (void *)&all->vis->param;
	win = all->vis->win;
	mlx_hook(win, KEY_PRESS, KEY_PRESS_MASK, ft_deal_key, param);
	mlx_hook(win, MOTION_NOTIFY, POINTER_MOTION_MASK, ft_mouse_move,
			(void *)all);
	mlx_hook(win, BUTTON_PRESS, BUTTON_PRESS_MASK, ft_mouse_press,
			(void *)all);
	mlx_hook(win, BUTTON_RELEASE, BUTTON_RELEASE_MASK, ft_mouse_release,
			(void *)all);
	mlx_loop_hook(all->vis->mlx, ft_loop_hook, (void *)all);
}
