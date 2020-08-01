/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:12:06 by ssoraka           #+#    #+#             */
/*   Updated: 2020/01/12 18:12:06 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collections_header.h"
#include "collections_help_header.h"

void	*ft_arr_get(t_arr *arr, int num)
{
	if (!arr || num < 0 || arr->elems_used < num + 1)
		return (NULL);
	return (arr->value(arr->elems + arr->elem_size * num));
}

void	*ft_arr_get_addr(t_arr *arr, int num)
{
	if (!arr || num < 0 || arr->elems_used < num + 1)
		return (NULL);
	return (arr->elems + arr->elem_size * num);
}

void	*ft_arr_get_next(t_arr *arr)
{
	if (!arr || !arr->elems)
		return (NULL);
	(arr->next)++;
	if (arr->next < (size_t)arr->elems_used)
		arr->current += arr->elem_size;
	else
	{
		arr->next = NEXT_START;
		arr->current = (char *)arr->elems - arr->elem_size;
		return (NULL);
	}
	return (arr->value((void *)arr->current));
}
