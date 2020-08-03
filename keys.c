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
#define MAX_RADIUS 20000
#define MIN_SCALE 0.01
#define MAX_SCALE 1000.0

int		ft_proection(t_param *param, int key)
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

int		ft_rotate_or_shift(t_param *param, int key)
{
	if (key == KEY_Q)
		param->ang.z += M_PI / CAM_ROTATE;
	else if (key == KEY_A)
		param->ang.z -= M_PI / CAM_ROTATE;
	else if (key == KEY_W)
		param->ang.y += M_PI / CAM_ROTATE;
	else if (key == KEY_S)
		param->ang.y -= M_PI / CAM_ROTATE;
	else if (key == KEY_E)
		param->ang.x += M_PI / CAM_ROTATE;
	else if (key == KEY_D)
		param->ang.x -= M_PI / CAM_ROTATE;
	else if (key == KEY_RIGHT)
		param->target_x += CAM_SHIFT;
	else if (key == KEY_LEFT)
		param->target_x -= CAM_SHIFT;
	else if (key == KEY_UP)
		param->target_y -= CAM_SHIFT;
	else if (key == KEY_DOWN)
		param->target_y += CAM_SHIFT;
	else
		return (FALSE);
	ft_rotate_xyz(&(param->oxyz), &(param->ang));
	return (TRUE);
}

int		ft_persp_and_csale(t_param *param, int key)
{
	if (key == KEY_PLUS && param->len < MAX_SCALE)
		param->len *= CAM_SCALE;
	else if (key == KEY_MINUS && param->len > MIN_SCALE)
		param->len /= CAM_SCALE;
	else if (key == KEY_O && param->radius > MIN_RADIUS)
		param->radius -= PERSP_SPEED;
	else if (key == KEY_I && param->radius < MAX_RADIUS)
		param->radius += PERSP_SPEED;
	else if (key == KEY_P)
		param->perspective++;
	else
		return (FALSE);
	if (param->perspective == LAST_PERSPECTIVE)
		param->perspective = NO_PERSPECTIVE;
	return (TRUE);
}

int		ft_csale_picture(t_param *param, int button, t_point *mouse)
{
	if (button == MIDDLE_FORW_BUTTON && param->len < MAX_SCALE)
		param->len *= CAM_SCALE;
	else if (button == MIDDLE_BACK_BUTTON && param->len > MIN_SCALE)
		param->len /= CAM_SCALE;
	else if (button == LEFT_BUTTON)
	{
		ft_fill_point(&param->first_pos, mouse->y, mouse->x, 0);
		param->left_button_press = TRUE;
	}
	else if (button == MIDDLE_BUTTON)
	{
		ft_fill_point(&param->pos, mouse->y, mouse->x, 0);
		param->right_button_press = TRUE;
	}
	else
		return (FALSE);
	return (TRUE);
}

int		ft_deal_key(int key, void *parametrs)
{
	t_param *param;

	printf("кнопка %d\n", key);
	param = (t_param *)parametrs;
	if (ft_rotate_or_shift(param, key) || ft_proection(param, key)
	|| ft_persp_and_csale(param, key))
		param->is_points_change = TRUE;
	else if (key == KEY_K)
		param->is_poligons_need_print = !param->is_poligons_need_print;
	else if (key == KEY_G)
		param->grad = !param->grad;
	else if (key == KEY_C)
		param->is_creating++;
	else if (key == KEY_ESC)
		param->exit = TRUE;
	else if (key == KEY_Z)
		param->coeff_z += DELTA_Z;
	else if (key == KEY_X)
		param->coeff_z -= DELTA_Z;
	else
		return (FAIL);
	param->is_points_change = TRUE;
	return (SUCCESS);
}
