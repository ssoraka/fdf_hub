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

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "mlx.h"
#include "../libft/libft.h"
#include "collections/collections_header.h"
#include "./includes/ft_fdf.h"


#define ABS(nbr) ((nbr) >= 0 ? (nbr) : (-1) * (nbr))



// t_vektr *parser_string(char *str, int row)
// {
// 	int column;
// 	t_vektr *begin;
// 	t_vektr *v;

// 	column = 0;
// 	begin = ft_new_vektor(column, row, ft_atoi(str));
// 	while (ft_isdigit(*str) || *str == '-')
// 		str++;
// 	v = begin;
// 	while (*str)
// 	{
// 		//надо сделать функции, которые будут возвращать указатель на строку с цифрой и с цветом
// 		while (ft_isspace(*str))
// 			str++;
// 		column++;
// 		v->next = ft_new_vektor(column, row, ft_atoi(str));
// 		while (ft_isdigit(*str) || *str == '-')
// 			str++;
// 		v = v->next;
// 	}
// 	if (max_x < column)
// 		max_x = column;
// 	return (begin);
// }


// t_vektr *pars_file(int fd)
// {
// 	char *line;
// 	t_vektr *begin;
// 	t_vektr *v;
// 	int row;

// 	row = 0;
// 	if (get_next_line(fd, &line) < 1)
// 		return (NULL);
// 	begin = parser_string(line, row);
// 	v = begin;
// 	while (get_next_line(fd, &line))
// 	{
// 		row++;
// 		v->down = parser_string(line, row);
// 		free(line);
// 		v = v->down;
// 	}
// 	if (max_y < row)
// 		max_y = row;
// 	return (begin);
// }

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

// void ft_add_line(t_line **begin, t_vektr *p1, t_vektr *p2)
// {
// 	t_line *line;
// 	t_line *tmp;

// 	line = ft_new_line(p1, p2, 0xFFFFFF);

// 	if (!line)
// 		return ;
// 	tmp = *begin;
// 	*begin = line;
// 	line->next = tmp;
// }


// int ft_lines_from_points(t_line **begin, t_vektr *point)
// {
// 	t_line *line;
// 	t_vektr *p1;
// 	t_vektr *p2;

// 	while (point)
// 	{
// 		p1 = point;
// 		point = point->down;
// 		p2 = point;
// 		while (p1->next)
// 		{
// 			ft_add_line(begin, p1, p1->next);
// 			ft_add_line(begin, p1, p2);
// 			p1 = p1->next;
// 			if (p2 && p2->next)
// 				p2 = p2->next;
// 		}
// 		p1->next = point;
// 		ft_add_line(begin, p1, p2);
// 	}
// 	return (0);
// }



// void ft_shift_points_to_center()
// {
// 	t_vektr *p;
// 	int delta_z;

// 	p = points;
// 	while (p)
// 	{
// 		if (p->otn_z > max_z)
// 			max_z = p->otn_z;
// 		if (p->otn_z < min_z)
// 			min_z = p->otn_z;
// 		p = p->next;
// 	}

// 	//printf("%d_%d_%d\n",delta_z, max_z, min_z);
// 	delta_z = max_z - min_z;
// 	p = points;
// 	while (p)
// 	{
// 		p->color = ft_grad_color(p->otn_z - min_z, delta_z, 0xFF0000, 0xFF00);
// 		p->otn_x = p->otn_x * 2;
// 		p->otn_y = p->otn_y * 2;
// 		p->otn_z = p->otn_z;
// 		p->otn_x = p->otn_x - max_x;
// 		p->otn_y = p->otn_y - max_y;
// 		// if (p->otn_z == 0)
// 		// 	p->color = 0xFF;
// 		// else
// 		// 	p->color = 0xFF0000;
// 		p = p->next;
// 	}

// }

int		ft_create_right_line(t_vektr *curr, t_vektr *next, t_line *line, t_arr *lines)
{
	if (next->abs.x == curr->abs.x + 1.0 && next->abs.y == curr->abs.y)
	{
		line->p1 = curr;
		line->p2 = next;
		if (!ft_arr_add(lines, (void *)line))
			return (FAIL);
	}
	return (SUCCESS);
}

int		ft_create_down_line(t_vektr *curr, t_vektr *down, t_line *line, t_arr *lines)
{
	if (down->abs.x == curr->abs.x && down->abs.y == curr->abs.y + 1.0)
	{
		line->p1 = curr;
		line->p2 = down;
		if (!ft_arr_add(lines, (void *)line))
			return (FAIL);
	}
	return (SUCCESS);
}

int		ft_create_lines_from_points(t_arr *points, t_arr *lines)
{
	t_vektr *curr;
	t_vektr *down;
	t_vektr *last;
	t_line line;

	ft_bzero((void *)&line, sizeof(t_line));
	last = ft_arr_get(points, points->elems_used - 1);
	down = ft_arr_get(points, 0);
	while ((curr = (t_vektr *)ft_arr_get_next(points)) && curr != last)
	{
		if (ft_create_right_line(curr, curr + 1, &line, lines) == FAIL)
			return (FAIL);
		while (down->abs.y <= curr->abs.y && down != last)
			down++;
		while (down->abs.y == curr->abs.y + 1 && down->abs.x < curr->abs.x && down != last)
			down++;
		if (ft_create_down_line(curr, down, &line, lines) == FAIL)
			return (FAIL);
	}
	return(SUCCESS);
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
	return (SUCCESS);
}

void	ft_exit(t_all *all, char *error_message)
{
	if (all->points)
		ft_del_arr(&all->points);
	if (all->lines)
		ft_del_arr(&all->lines);
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
	
	// mlx_hook(win_ptr, 2, 0, deal_key, (void *)0);
	// mlx_loop(mlx_ptr);

	ft_exit(&all, NULL);
	return (0);
}


