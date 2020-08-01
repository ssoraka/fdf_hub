/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:23:42 by ssoraka           #+#    #+#             */
/*   Updated: 2019/03/07 16:22:42 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_fdf.h"

void	ft_print_all_lines(t_arr *lines, t_pict *pic, t_param *param)
{
	t_line line;
	t_vektr **v;
	int i;
	int count;

    line.color = DEFAULT_LINE_COLOR;
    count = lines->elems_used / 2;
    v = (t_vektr **)lines->elems;
    i = 0;
    while (i < count)
	{
        line.index = DEFAULT_INDEX;
	    line.p1 = *(v++);
	    line.p2 = *(v++);
	    if (!(line.p1->zoom.x == UNPRINTABLE && line.p1->zoom.y == UNPRINTABLE)
	    && !(line.p2->zoom.x == UNPRINTABLE && line.p2->zoom.y == UNPRINTABLE))
            draw_line_img(&line, pic, param->grad);
        i++;
	}
}

void	ft_print_all_poligons(t_arr *plgns, t_pict *pic, t_param *param)
{
    t_plgn *plgn;
    int i;
    int count;

    count = plgns->elems_used;
    plgn = (t_plgn *)plgns->elems;
    i = 0;
    while (i < count)
    {
        ft_prepare_plgn_for_printing(plgn, param);
        ft_print_plgn(plgn, pic, param->grad);
        plgn++;
        i++;
    }
}

void	ft_print_all_points(t_arr *points, t_pict *pic, t_param *param)
{
    t_vektr *v;
    int i;
    int count;
    t_shape shape;

    ft_init_shape(&shape, POINT_INDEX, FALSE);

    count = points->elems_used;
    v = (t_vektr *)points->elems;
    i = 0;
    while (i < count)
    {
        shape.index = i + 1;
        shape.print(pic, &(v->zoom), &shape);
        v++;
        i++;
    }
}

void	ft_rotate_all_points(t_arr *points, t_param *param)
{
	t_vektr *v;
	int i;
	int count;

    ft_rotate_point_around_point(param, param->centr, &param->centr->abs);
    param->centr->zoom.x = param->cam_x;
    param->centr->zoom.y = param->cam_y;

	count = points->elems_used;
	v = ft_arr_get(points, 0);

    i = 0;
    while (i < count)
	{
		// ft_change_points(param, v + i);
		ft_rotate_point_around_point(param, v + i, &param->centr->abs);
		i++;
	}
}

int		ft_move_camera(t_param *param)
{
	int dx[2];
	int dy[2];
	int bigest;

    if (param->target_x == param->cam_x && param->target_y == param->cam_y)
		return (FALSE);
//    dx[0] = param->target_x - param->cam_x;
//    dy[0] = param->target_y - param->cam_y;
//
//    dx[1] = ft_max(dx[0], -dx[0]);
//    dy[1] = ft_max(dy[0], -dy[0]);
//    bigest = ft_max(dx[1], dy[1]);
//
//    param->cam_x += (dx[0] * SPEED) / bigest;
//    param->cam_y += (dy[0] * SPEED) / bigest;
//	if (dx[1] <= SPEED)
		param->cam_x = param->target_x;
//	if (dy[1] <= SPEED)
		param->cam_y = param->target_y;
	return (TRUE);
}

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

//int     ft_activate_nearest_elem(t_all *all, t_param *param)
//{
//    int id;
//
//    if (param->near_id == DEFAULT_INDEX)
//        return (FALSE);
//    //param->cam_x = param->centr->zoom.x;
//    //param->cam_y = param->centr->zoom.y;
//    param->active_id = param->near_id;
//    param->act[0] = NULL;
//    param->act[1] = NULL;
//    if (param->near_id > 0)
//    {
//        id = param->near_id - 1;
//        param->act[0] = ft_arr_get(all->points, id);
//    }
//    else
//    {
//        id = -param->near_id - 1;
//        param->act[0] = ft_arr_get(all->lines, id * 2);
//        param->act[1] = ft_arr_get(all->lines, id * 2 + 1);
//    }
//    param->near_id = DEFAULT_INDEX;
//    return (TRUE);
//}

t_vektr *ft_get_nearest_point(t_all *all, t_param *param)
{
    int id;
    t_vektr *v;

    if (param->near_id == DEFAULT_INDEX)
        return (NULL);
    if (param->near_id > 0)
    {
        param->active_id = param->near_id;
        id = param->near_id - 1;
        v = (t_vektr *)ft_arr_get(all->points, id);
    }
    param->near_id = DEFAULT_INDEX;
    return (v);
}

void    ft_try_change_active_point(t_param *param, t_vektr *active)
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


int		ft_mouse_press(int button, int x, int y, void *parameters)
{
	t_all *all;
	t_param *param;
	t_vektr *active;

	all = (t_all *)parameters;
	param = &all->vis->param;
	if (param->exit || !ft_mouse_on_window(x, y))
		return (0);
//	printf("___BUTTON %d\n", button);
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

int     ft_is_cam_moved(t_param *param)
{
    if (param->right_button_press)
    {
        param->target_x = param->target_x + param->mouse.x - param->pos.x;
        param->target_y = param->target_y + param->mouse.y - param->pos.y;
        param->pos.x = param->mouse.x;
        param->pos.y = param->mouse.y;
        return(TRUE);
    }
    return(FALSE);
}

int     ft_is_cam_rotated(t_param *param)
{
    double len;

    if (param->left_button_press)
    {
        len = sqrt(pow(param->mouse.y - param->first_pos.y, 2.0)
                + pow(param->mouse.x - param->first_pos.x, 2.0));
        ft_fill_point(&param->rot_pos,
                param->mouse.y - param->first_pos.y,
                param->mouse.x - param->first_pos.x, 0);
        param->rounds = (int)(len / 25);
        return(TRUE);
    }
    return(FALSE);
}

int		ft_mouse_move(int x, int y, void *parameters)
{
	t_all *all;
	t_param *param;

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


int		ft_mouse_release(int button, int x, int y, void *parameters)
{
	t_all *all;
	t_param *param;

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

int		ft_auto_rotate(t_param *param)
{
	t_dpoint v;

	if (param->rounds > 0)
	{
		(param->rounds)--;
		ft_fill_dpoint(&v, -param->rot_pos.x, param->rot_pos.y, 0.0);

        ft_rotate_xyz_around_v(&param->oxyz, &v, ROTATE_ANGLE);
		return (TRUE);
	}
	return (FALSE);
}


/*
нужно сделать так, чтоб прои движении курсора определялась ближайшая точка
в пределахуказанного радиуса
эта точка становится подсвечивается
иначе ищутся ближайшие линии и подсвечивается
при клике мышкой подсвечивающийся объект доступен изменению

выбранную линию можно удалять
точку передвигать
*/
int		ft_loop_hook(void *param)
{
	t_all *all;
	t_vis *vis;

	all = (t_all *)param;
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
        ft_print_all_points(all->points, &(vis->pic), &(vis->param));
        ft_print_active(&(vis->pic), &(vis->param));
        ft_print_front(&(vis->pic), &(vis->param));
//		ft_memcpy((void *)vis->pic.addr, (void *)vis->pic.index, vis->pic.count_byte);
	}
    mlx_put_image_to_window(vis->mlx, vis->win, vis->pic.img, 0, 0);
    mlx_do_sync(all->vis->mlx);
    return (0);
}

int 	ft_init_all(t_all *all)
{
	ft_bzero((void *)all, sizeof(t_all));
	if (!(all->points = ft_create_arr(sizeof(t_vektr), 10, NULL)))
		return (FAIL);
	if (!(all->lines = ft_create_arr_of_ptr(10, NULL)))
		return (FAIL);
    if (!(all->plgns = ft_create_arr(sizeof(t_plgn), 10, NULL)))
        return (FAIL);
	if (!(all->vis = ft_create_mlx(CONST_WIDTH, CONST_HEINTH, "fdf")))
		return (FAIL);
	return (SUCCESS);
}

void	ft_exit(t_all *all, char *error_message)
{
	if (all->points)
		ft_del_arr(&all->points);
	if (all->lines)
		ft_del_arr(&all->lines);
    if (all->plgns)
        ft_del_arr(&all->plgns);
	if (all->vis)
		ft_destroy_mlx(&all->vis);
	if (error_message)
	{
		ft_putendl_fd(error_message, 2);
		exit(1);
	}
	exit(0);
}

int     ft_print_usage()
{
    ft_putendl("usage:");
    ft_putendl("./fdf map");
    ft_putendl("");
    ft_putendl("where map is file with numbers:");
    ft_putendl("0 1 1");
    ft_putendl("1 2 1");
    ft_putendl("0 0 -1");
    ft_putendl("");
    ft_putendl("Key control:");
    ft_putendl("Q,W,E,A,S,D, LEFT MOUSE - rotate");
    ft_putendl("UP,DOWN,LEFT,RIGHT,MIDDLE MOUSE - shift");
    ft_putendl("+,-,MIDDLE ROTATE MOUSE - backtrack");
    ft_putendl("RIGHT MOUSE - change rotate center");
    ft_putendl("Z/X - increase/decrease z coordinate");
    ft_putendl("P - change prospect");
    ft_putendl("O/I - increase/decrease prospect");
    ft_putendl("G - gradient");
    ft_putendl("C - first press allow mark 2-3 point");
    ft_putendl("C - second press create new lines and polygon");
    return (0);
}

int		main(int argc, char **argv)
{
	t_all all;
	int status;

	if (argc == 1)
        return (ft_print_usage());
	if (ft_init_all(&all) == FAIL)
		ft_exit(&all, MSG_ERROR1);
	if ((status = ft_points_from_file(argv[1], all.points)) != NO_ERR)
		ft_exit(&all, (char *)MSG_ERROR1 + (status - 1) * 14);
	if (ft_create_pair_from_points(all.points, all.lines) == FAIL)
		ft_exit(&all, MSG_ERROR1);
    if (ft_poligons_from_points(all.points, all.plgns) == FAIL)
        ft_exit(&all, MSG_ERROR1);

	printf("lines count = %d\n", all.lines->elems_used);
	printf("polig count = %d\n", all.plgns->elems_used);

    all.vis->param.centr = ft_arr_get(all.points, 0);

    mlx_hook(all.vis->win, KEY_PRESS, KEY_PRESS_MASK, ft_deal_key, (void *)&all.vis->param);
//    mlx_hook(all.vis->win, KEY_RELEASE, KeyReleaseMask, ft_deal_key_release, (void *)&all.vis->param);
	mlx_hook(all.vis->win, MOTION_NOTIFY, POINTER_MOTION_MASK, ft_mouse_move, (void *)&all);
    mlx_hook(all.vis->win, BUTTON_PRESS, BUTTON_PRESS_MASK, ft_mouse_press, (void *)&all);
	mlx_hook(all.vis->win, BUTTON_RELEASE, BUTTON_RELEASE_MASK, ft_mouse_release, (void *)&all);
	mlx_loop_hook(all.vis->mlx, ft_loop_hook, (void *)&all);
	mlx_loop(all.vis->mlx);

	ft_exit(&all, NULL);
	return (0);
}
