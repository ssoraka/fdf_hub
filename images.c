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


/*
** надо пачку защит маллока наставить ...
*/

void	ft_init_params(t_param *param)
{
	param->cam_x = CAM_X;
	param->cam_y = CAM_Y;
	param->target_x = CAM_X;
	param->target_y = CAM_Y;
	param->len = CONST_LEN;
	 param->light.x = 0.5;
	 param->light.y = -1;
	 param->light.z = 1;
	param->is_points_change = TRUE;
	ft_create_xyz(&(param->oxyz));
}


void	ft_clear_image(t_pict *pic)
{
    ft_memset8((void *)pic->index, DEFAULT_INDEX, pic->count_byte);
	ft_memset8((void *)pic->addr, BACKGROUND_COLOR, pic->count_byte);
	ft_memset8((void *)pic->z_buffer, MIN_INTEGER, pic->count_byte);
}

//void	ft_return_image(t_pict *pic)
//{
//	ft_memcpy8((void *)pic->addr, (void *)pic->addr_copy, pic->count_byte);
//	ft_memcpy8((void *)pic->z_buffer, (void *)pic->z_buffer_copy, pic->count_byte);
//}

//void	ft_save_image(t_pict *pic)
//{
//	ft_memcpy8((void *)pic->addr_copy, (void *)pic->addr, pic->count_byte);
//	ft_memcpy8((void *)pic->z_buffer_copy, (void *)pic->z_buffer, pic->count_byte);
//}

int		ft_create_img(t_pict *pic, void *mlx, int width, int heigth)
{
	if (!(pic->img = mlx_new_image(mlx, width, heigth)))
		return (FALSE);
	if (!(pic->addr = (int *)mlx_get_data_addr(pic->img, &(pic->bits_per_pixel), &(pic->size_line), &(pic->endian))))
		return (FALSE);
	pic->count_line = heigth;
	pic->count_byte = width * heigth * sizeof(int);
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



int		ft_not_need_print(t_line *line, t_pict *pic)
{
	if (line->p1->zoom.y <= 0 && line->p2->zoom.y <= 0)
		return (TRUE);
	if (line->p1->zoom.x <= 0 && line->p2->zoom.x <= 0)
		return (TRUE);
	if (line->p1->zoom.y >= CONST_HEINTH && line->p2->zoom.y >= CONST_HEINTH)
		return (TRUE);
	if (line->p1->zoom.x >= CONST_WIDTH && line->p2->zoom.x >= CONST_WIDTH)
		return (TRUE);
	//хз, спорное условие...
	/*if (line->p1->zoom.x >= 0 && line->p1->zoom.x < CONST_WIDTH
	&& line->p1->zoom.y >= 0 && line->p1->zoom.y < CONST_HEINTH
	&& pic->z_buffer[line->p1->zoom.y * CONST_WIDTH + line->p1->zoom.x] > line->p1->zoom.z + 10
	&& line->p2->zoom.x >= 0 && line->p2->zoom.x < CONST_WIDTH
	&& line->p2->zoom.y >= 0 && line->p2->zoom.y < CONST_HEINTH
	&& pic->z_buffer[line->p2->zoom.y * CONST_WIDTH + line->p2->zoom.x] > line->p2->zoom.z + 10)
		return (TRUE);*/
	return (FALSE);
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
