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


#define ABS(nbr) ((nbr) >= 0 ? (nbr) : (-1) * (nbr))


void	ft_print_all_lines(t_arr *lines, t_pict *pic, t_param *param)
{
	t_line *line;
	int i;
	int count;

	count = lines->elems_used;
	line = ft_arr_get(lines, 0);
	i = 0;
	while (i < count)
	{
		draw_line_img(line + i, pic, param->grad);
		i++;
	}
}

void	ft_rotate_all_points(t_arr *points, t_pict *pic, t_param *param)
{
	t_vektr *v;
	int i;
	int count;

	count = points->elems_used;
	v = ft_arr_get(points, 0);
	i = 0;
	while (i < count)
	{
		ft_change_points(param, v + i);
		// ft_print_rect(pic, &((v + i)->zoom), 10, 0xFFFFFF);
		circle(pic, v + i, 10, 0xFFFFFF);
		i++;
	}
}


int		ft_key_hook(int key, void *param)
{
	t_all *all;
	t_vis *vis;

	all = (t_all *)param;
	vis = all->vis;
	if (ft_deal_key(key, &vis->param) == FAIL)
		ft_exit(all, NULL);


	mlx_clear_window(vis->mlx, vis->win);
	ft_clear_image(&(vis->pic));

	ft_rotate_all_points(all->points, &(vis->pic), &(vis->param));
	ft_print_all_lines(all->lines, &(vis->pic), &(vis->param));
	//ft_memcpy((void *)vis->pic.addr, (void *)vis->pic.index, vis->pic.count_byte);

	mlx_put_image_to_window(vis->mlx, vis->win, vis->pic.img, 0, 0);

	return (0);
}




void ft_print_points(void *elem, void *param)
{
	t_vektr *v = (t_vektr *)elem;

	printf("%.f_%.f_%.f\n", v->abs.x, v->abs.y, v->abs.z);
}

void ft_print_lines(void *elem, void *param)
{
	t_vektr *v = ((t_line *)elem)->p1;
	t_vektr *v1 = ((t_line *)elem)->p2;

	printf("%.f__%.f\n", v->abs.z, v1->abs.z);
	// printf("%.f_%.f_%.f___%.f_%.f_%.f\n", v->abs.x, v->abs.y, v->abs.z, v1->abs.x, v1->abs.y, v1->abs.z);
}


int 	ft_init_all(t_all *all)
{
	ft_bzero((void *)all, sizeof(t_all));
	if (!(all->points = ft_create_arr(sizeof(t_vektr), 10, NULL)))
		return (FAIL);
	if (!(all->lines = ft_create_arr(sizeof(t_line), 10, NULL)))
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
	if (all->vis)
		ft_destroy_mlx(&all->vis);
	if (error_message)
	{
		ft_putendl_fd(error_message, 2);
		exit(1);
	}
	exit(0);
}

int main()
{
	t_all all;

	if (ft_init_all(&all) == FAIL)
		ft_exit(&all, MSG_ERROR1);
	if (ft_points_from_file("text.txt", all.points) == FAIL)
		ft_exit(&all, MSG_ERROR1);
	if (ft_create_lines_from_points(all.points, all.lines) == FAIL)
		ft_exit(&all, MSG_ERROR1);
	ft_for_each_elem(all.points, &ft_print_points, NULL);
	ft_for_each_elem(all.lines, &ft_print_lines, NULL);
	// ft_shift_points_to_center(points);
	// ft_lines_from_points(&begin_line, begin_point);
	
	mlx_hook(all.vis->win, 2, 0, ft_key_hook, (void *)&all);
	mlx_loop(all.vis->mlx);

	ft_exit(&all, NULL);
	return (0);
}


