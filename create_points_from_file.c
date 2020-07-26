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

REAL	ft_max_mytype(REAL first, REAL second)
{
	if (first > second)
		return (first);
	return (second);
}

REAL	ft_min_mytype(REAL first, REAL second)
{
	if (first < second)
		return (first);
	return (second);
}

void	ft_change_points_color(t_arr *points)
{
	t_vektr *p;
	REAL max_z;
	REAL min_z;
	int tmp;
	int tmp2;

	p = ft_arr_get(points, 0);
	max_z = p->abs.z;
	min_z = p->abs.z;
	while ((p = (t_vektr *)ft_arr_get_next(points)))
	{
		max_z = ft_max_mytype(max_z, p->abs.z);
		min_z = ft_min_mytype(min_z, p->abs.z);
	}
	while ((p = (t_vektr *)ft_arr_get_next(points)))
	{
		tmp = (int)p->abs.z * 2;
		tmp2 = min_z * 2 + (max_z - min_z);
		if (p->color != DEFAULT_COLOR)
			continue ;
		p->color = ZERO_COLOR;
		if (tmp >= tmp2 && (int)(max_z - min_z))
			p->color = ft_grad_color(tmp - tmp2, (int)(max_z - min_z), UP_COLOR, ZERO_COLOR);
		else if ((int)(max_z - min_z))
			p->color = ft_grad_color(tmp2 - tmp, (int)(max_z - min_z), DOWN_COLOR, ZERO_COLOR);
	}
}

t_stat	ft_get_num_and_color_from_string(char **string, int *z, int *color)
{
    char *str;

    str = *string;
    if (!ft_isdigit(*str) && *str != '-')
        return (VALIDATION_ERROR);
    *z = ft_atoi(str);
    if (*str == '-')
        str++;
    while (*str && ft_isdigit(*str))
        str++;
    *color = DEFAULT_COLOR;
    *string = str;
    if (ft_strncmp(str, ",0x", 3))
        return (NO_ERR);
    str = str + 3;
    *color = ft_atoi_base(str, 16);
    while (*str && ft_strchr("0123456789abcdefABCDEF", *str))
        str++;
    if (*str && !ft_isspace(*str))
        return (VALIDATION_ERROR);
    *string = str;
    return (NO_ERR);
}


t_stat  ft_string_to_points(char *str, t_arr *points, int y)
{
	int x;
	int z;
	t_vektr tmp;

	x = 0;
	ft_bzero((void *)&tmp, sizeof(t_vektr));
	while (*str)
	{
		while (*str && ft_isspace(*str))
			str++;
        if (!(*str))
            return (NO_ERR);
        if (ft_get_num_and_color_from_string(&str, &z, &tmp.color) != NO_ERR)
            return (VALIDATION_ERROR);
		ft_fill_dpoint(&(tmp.abs), y, x, z);
		if (!ft_arr_add(points, &tmp))
            return (MALLOC_ERROR);
		while (*str && (ft_isdigit(*str) || *str == '-'))
			str++;
		x++;
	}
	return (NO_ERR);
}

t_stat  ft_points_from_file(char *name, t_arr *points)
{
	char	*str;
	int		fd;
	int		row;
	int		status;

	if ((fd = open(name, O_RDWR)) < 0)
		return (FILE_ERROR);
    status = NO_ERR;
	row = 0;
	while (get_next_line(fd, &str) > 0 && status == NO_ERR)
	{
        status = ft_string_to_points(str, points, row);
		free(str);
		row++;
	}
	close(fd);
	ft_change_points_color(points);
	return (status);
}