/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 18:12:08 by ssoraka           #+#    #+#             */
/*   Updated: 2019/10/27 18:12:08 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_fdf.h"

#define CAM_SHIFT 20
#define CAM_SCALE 1.1
#define CAM_ROTATE 90
#define PERSP_SPEED 4
#define MIN_RADIUS 500
#define MAX_RADIUS 5000


#define MIN_SCALE 0.01
#define MAX_SCALE 1000.0

int     ft_proection(t_param *param, int key)
{
    t_dpoint v;

    if (key != KEY_1 && key != KEY_2 && key != KEY_3)
        return (FALSE);
    ft_create_xyz(&(param->oxyz));
    if (key == KEY_2)
    {
        ft_fill_dpoint(&v, 0.0, 0.0, 1.0);
        ft_rotate_xyz_around_v(&param->oxyz, &v, M_PI * 0.750);
        ft_fill_dpoint(&v, 0.0, 1.0, 0.0);
        ft_rotate_xyz_around_v(&param->oxyz, &v, M_PI * 1.250);
    }
    if (key == KEY_3)
    {
        ft_fill_dpoint(&v, 0.0, 0.0, 1.0);
        ft_rotate_xyz_around_v(&param->oxyz, &v, M_PI * 0.750);
        ft_fill_dpoint(&v, 0.0, 1.0, 0.0);
        ft_rotate_xyz_around_v(&param->oxyz, &v, M_PI * 1.250);
        ft_fill_dpoint(&v, 1.0, 0.0, 0.0);
        ft_rotate_xyz_around_v(&param->oxyz, &v, M_PI);
    }
    return (TRUE);
}

int		ft_rotate_and_csale(t_param *vis, int key)
{
	if (key == KEY_PLUS && vis->len < MAX_SCALE)
		vis->len *= CAM_SCALE;
	else if (key == KEY_MINUS && vis->len > MIN_SCALE)
		vis->len /= CAM_SCALE;
	else if (key == KEY_Q)
		vis->ang.z += M_PI / CAM_ROTATE;
	else if (key == KEY_A)
		vis->ang.z -= M_PI / CAM_ROTATE;
	else if (key == KEY_W)
		vis->ang.y += M_PI / CAM_ROTATE;
	else if (key == KEY_S)
		vis->ang.y -= M_PI / CAM_ROTATE;
	else if (key == KEY_E)
		vis->ang.x += M_PI / CAM_ROTATE;
	else if (key == KEY_D)
		vis->ang.x -= M_PI / CAM_ROTATE;
    else if (key == KEY_O && vis->radius > MIN_RADIUS)
        vis->radius -= PERSP_SPEED;
    else if (key == KEY_I && vis->radius < MIN_RADIUS)
        vis->radius += PERSP_SPEED;
    else if (key == KEY_C)
        vis->is_creating++;
	else if (!ft_proection(vis, key))
		return (FALSE);
	ft_rotate_xyz(&(vis->oxyz), &(vis->ang));
	return (TRUE);
}





int		ft_csale_picture(t_param *vis, int button, t_point *mouse)
{
	if (button == MIDDLE_FORW_BUTTON && vis->len < MAX_SCALE)
		vis->len *= CAM_SCALE;
	else if (button == MIDDLE_BACK_BUTTON && vis->len > MIN_SCALE)
		vis->len /= CAM_SCALE;
	else if (button == LEFT_BUTTON)
	{
		ft_fill_point(&vis->first_pos, mouse->y, mouse->x, 0);
		vis->left_button_press = TRUE;
	}
	else if (button == MIDDLE_BUTTON)
	{
		ft_fill_point(&vis->pos, mouse->y, mouse->x, 0);
		vis->right_button_press = TRUE;
	}
	else
		return (FALSE);
	//ft_rotate_xyz(&(vis->oxyz), &(vis->ang));
	return (TRUE);
}


int		ft_shift(t_param *vis, int key)
{
	if (key == KEY_RIGHT)
		vis->target_x += CAM_SHIFT;
	else if (key == KEY_LEFT)
		vis->target_x -= CAM_SHIFT;
	else if (key == KEY_UP)
		vis->target_y -= CAM_SHIFT;
	else if (key == KEY_DOWN)
		vis->target_y += CAM_SHIFT;
	else
		return (FALSE);
	return (TRUE);
}

/*
int     ft_deal_key_release(int key, void *parametrs)
{
    printf("release %d\n", key);
    return (SUCCESS);
}
 */

int		ft_deal_key(int key, void *parametrs)
{
	t_param *param;

	param = (t_param *)parametrs;
	printf("%d\n", key);
	if (ft_rotate_and_csale(param, key) || ft_shift(param, key))
		param->is_points_change = TRUE;
    else if (key == KEY_P)
    {
        param->perspective++;
        if (param->perspective == LAST_PERSPECTIVE)
            param->perspective = NO_PERSPECTIVE;
    }
    else if (key == KEY_K)
        param->is_poligons_need_print = !param->is_poligons_need_print;
    else if (key == KEY_G)
		param->grad = !param->grad;
    else if (key == KEY_ESC)
		param->exit = TRUE;
    else
        return (FAIL);
    param->is_points_change = TRUE;
	return (SUCCESS);
}
