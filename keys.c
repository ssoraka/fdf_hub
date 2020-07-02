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

#define MIN_SCALE 0.01
#define MAX_SCALE 1000.0

#define KEY_PLUS 18
#define KEY_MINUS 19
#define KEY_Q 12
#define KEY_A 0
#define KEY_W 13
#define KEY_S 1
#define KEY_E 14
#define KEY_D 2
#define KEY_K 40
#define KEY_L 37

#define KEY_LEFT 123
#define KEY_RIGHT 124
#define KEY_UP 126
#define KEY_DOWN 125

#define KEY_ESC 53
#define KEY_P 35
#define KEY_O 31
#define KEY_R 15
#define KEY_G 5
#define KEY_I 34


int		ft_rotate_and_csale(t_param *vis, int key)
{
	if ((key == KEY_PLUS || key == 69) && vis->len < MAX_SCALE)
		vis->len *= CAM_SCALE;
	else if ((key == KEY_MINUS || key == 78) && vis->len > MIN_SCALE)
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
	else
		return (FALSE);
	ft_rotate_xyz(&(vis->oxyz), &(vis->ang));
	vis->cos.y = ft_vekt_cos(vis->oxyz.oy, vis->light);
	vis->cos.x = ft_vekt_cos(vis->oxyz.ox, vis->light);
	vis->cos.z = ft_vekt_cos(vis->oxyz.oz, vis->light);
	printf("%lf_%lf_%lf\n", vis->cos.y, vis->cos.x, vis->cos.z);
	return (TRUE);
}


int		ft_shift(t_param *vis, int key)
{
	if (key == KEY_RIGHT)
		vis->cam_x += CAM_SHIFT;
	else if (key == KEY_LEFT)
		vis->cam_x -= CAM_SHIFT;
	else if (key == KEY_UP)
		vis->cam_y -= CAM_SHIFT;
	else if (key == KEY_DOWN)
		vis->cam_y += CAM_SHIFT;
	else
		return (FALSE);
	return (TRUE);
}


int		ft_deal_key(int key, void *parametrs)
{
	t_param *param;

	printf("\n%d\n", key);
	param = (t_param *)parametrs;
	if (ft_rotate_and_csale(param, key) || ft_shift(param, key) || key == KEY_O
	|| key == KEY_G)
		param->is_points_change = TRUE;
	if (key == KEY_ESC)
		return (FAIL);
	if (key == KEY_P)
		param->pause = !param->pause;
	if (key == KEY_G)
		param->grad = !param->grad;
	return (SUCCESS);
}
