/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 18:28:19 by ssoraka           #+#    #+#             */
/*   Updated: 2019/10/27 18:28:20 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_fdf.h"

void	ft_init_params(t_param *param)
{
	param->cam_x = CAM_X;
	param->cam_y = CAM_Y;
	param->target_x = CAM_X;
	param->target_y = CAM_Y;
	param->len = CONST_LEN;
	param->radius = CONST_RADIUS;
	param->light.x = 0.5;
	param->light.y = -1;
	param->light.z = 1;
	param->coeff_z = 1.0;
	param->is_points_change = TRUE;
	ft_create_xyz(&(param->oxyz));
}

int		ft_create_img(t_pict *pic, void *mlx, int width, int height)
{
	if (!(pic->img = mlx_new_image(mlx, width, height)))
		return (FALSE);
	if (!(pic->addr = (int *)mlx_get_data_addr(pic->img, &(pic->bits_per_pixel),
			&(pic->size_line), &(pic->endian))))
		return (FALSE);
	pic->count_line = height;
	pic->count_byte = width * height * sizeof(int);
	if (!(pic->z_buffer = (int *)ft_memalloc(pic->count_byte)))
		return (FALSE);
	if (!(pic->addr_copy = (int *)ft_memalloc(pic->count_byte)))
		return (FALSE);
	if (!(pic->z_buffer_copy = (int *)ft_memalloc(pic->count_byte)))
		return (FALSE);
	if (!(pic->index = (int *)ft_memalloc(pic->count_byte)))
		return (FALSE);
	ft_clear_image(pic);
	return (TRUE);
}

void	ft_destroy_img(t_pict *pic)
{
	ft_memdel((void **)&(pic->z_buffer));
	ft_memdel((void **)&(pic->addr_copy));
	ft_memdel((void **)&(pic->z_buffer_copy));
	ft_memdel((void **)&(pic->index));
}

t_vis	*ft_create_mlx(int width, int heigth, char *name)
{
	t_vis *vis;

	if (!(vis = ft_memalloc(sizeof(t_vis))))
		return (NULL);
	if (!(vis->mlx = mlx_init()))
		return (ft_destroy_mlx(&vis));
	if (!(vis->win = mlx_new_window(vis->mlx, width, heigth, name)))
		return (ft_destroy_mlx(&vis));
	if (!(ft_create_img(&(vis->pic), vis->mlx, width, heigth)))
		return (ft_destroy_mlx(&vis));
	ft_init_params(&(vis->param));
	return (vis);
}

t_vis	*ft_destroy_mlx(t_vis **vis)
{
	if (*vis)
	{
		ft_destroy_img(&((*vis)->pic));
		mlx_destroy_image((*vis)->mlx, (*vis)->pic.img);
		mlx_destroy_window((*vis)->mlx, (*vis)->win);
		ft_memdel((void **)vis);
	}
	return (NULL);
}
