/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:12:06 by ssoraka           #+#    #+#             */
/*   Updated: 2020/01/12 18:12:06 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collections_header.h"
#include "collections_help_header.h"

t_arr	*ft_create_arr_of_elems(void *value, int elem_size,
		int elems_count, void (*func_del)(void *))
{
	t_arr *arr;

	arr = ft_create_arr(elem_size, elems_count, func_del);
	if (!arr)
		return (NULL);
	ft_all_arr_init_by_value(arr, value);
	arr->elems_used = arr->elems_count;
	return (arr);
}

void	ft_del_arr_without_del_content(t_arr *arr, t_ilist *ilist)
{
	void *elem;

	while ((elem = ft_arr_get_next(arr)))
		ilist->del_list_without_key_value(elem);
	arr->func_del = NULL;
	ft_del_arr(&arr);
}

int		ft_increase_hmap(t_hmap *hmap)
{
	t_hmap	tmp;
	void	*list;
	void	*value;
	void	*key;

	ft_memcpy((void *)&tmp, hmap, sizeof(t_hmap));
	tmp.elems_used = 0;
	tmp.max_load = tmp.arr->elems_used * 2 * HASHMAP_LOAD;
	tmp.arr = ft_create_arr_of_elems((void *)tmp.list.mem, hmap->list.size,
			hmap->arr->elems_used << 1, hmap->list.del);
	if (!tmp.arr)
		return (FALSE);
	while ((list = ft_arr_get_next(hmap->arr)))
		while (hmap->list.get_next(list, &key, &value))
			if (!ft_hashmap_put(&tmp, key, value))
			{
				ft_del_arr_without_del_content(tmp.arr, &tmp.list);
				return (FALSE);
			}
	ft_del_arr_without_del_content(hmap->arr, &hmap->list);
	hmap->arr = tmp.arr;
	hmap->max_load = tmp.max_load;
	return (TRUE);
}
