/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_points_from_file.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 20:59:39 by ssoraka           #+#    #+#             */
/*   Updated: 2019/04/19 13:13:30 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_fdf.h"

int		ft_get_color_from_string(char *str)
{
	while (ft_isdigit(*str) || *str == '-')
	{
		//надо сделать атоибейс
		if (*str == 'x')
			return (ft_atoi(str));
		str++;
	}
	return (WHITE_COLOR);
}

int		ft_string_to_points(char *str, t_arr *points, int y)
{
	int x;
	int z;
	t_vektr tmp;
	int has_err;

	x = 0;
	ft_bzero((void *)&tmp, sizeof(t_vektr));
	has_err = FALSE;
	while (*str)
	{
		while (ft_isspace(*str))
			str++;
		z = ft_atoi(str);
		ft_fill_dpoint(&(tmp.abs), y, x, z);
		tmp.color = ft_get_color_from_string(str);
		if (!ft_arr_add(points, &tmp))
		{
			has_err = TRUE;
			break ;
		}
		while (ft_isdigit(*str) || *str == '-')
			str++;
		x++;
	}
	return (has_err);
}


int		ft_points_from_file(char *name, t_arr *points)
{
	char	*str;
	int		fd;
	int		row;
	int		has_error;

	if ((fd = open(name, O_RDWR)) < 0)
		return (1);
	has_error = 0;
	row = 0;
	while (get_next_line(fd, &str) > 0 && !has_error)
	{
		if (ft_string_to_points(str, points, row) == FAIL)
			has_error = TRUE;
		free(str);
		row++;
	}
	close(fd);
	return (has_error);
}