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

int		ft_init_all(t_all *all)
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

int		ft_print_usage(void)
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
	t_all	all;
	int		status;

	if (argc != 2)
		return (ft_print_usage());
	if (ft_init_all(&all) == FAIL)
		ft_exit(&all, MSG_ERROR1);
	if ((status = ft_points_from_file(argv[1], all.points)) != NO_ERR)
		ft_exit(&all, (char *)MSG_ERROR1 + (status - 1) * 14);
	if (ft_create_pair_from_points(all.points, all.lines) == FAIL)
		ft_exit(&all, MSG_ERROR1);
	if (ft_polygons_from_points(all.points, all.plgns) == FAIL)
		ft_exit(&all, MSG_ERROR1);
	all.vis->param.centr = ft_arr_get(all.points, 0);
	ft_init_hooks(&all);
	mlx_loop(all.vis->mlx);
	ft_exit(&all, NULL);
	return (0);
}
