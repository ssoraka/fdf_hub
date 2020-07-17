
#include "libft.h"
#include "collections_header.h"


t_arr *ft_create_arr_of_elems(void *value, int elem_size, int elems_count, void (*func_del)(void *))
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
	tmp.arr = ft_create_arr_of_elems((void *)tmp.list.mem, hmap->list.size, hmap->arr->elems_used << 1, hmap->list.del);
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



int		ft_hashmap_put(t_hmap *hmap, void *key, void *value)
{
	int index;
	void *list;

	if (hmap->elems_used >= hmap->max_load)
		if (!ft_increase_hmap(hmap))
			return (FALSE);
	index = hmap->func_hash(key) & (hmap->arr->elems_used - 1);
	list = ft_arr_get(hmap->arr, index);
	if (!(hmap->list.add(list, key, value)))
		return (FALSE);
	hmap->elems_used++;
	return (TRUE);
}

void	*ft_hashmap_get(t_hmap *hmap, void *key)
{
	int index;
	void *list;

	index = hmap->func_hash(key) & (hmap->arr->elems_used - 1);
	list = ft_arr_get(hmap->arr, index);
	return (hmap->list.find(list, key));
}

void	ft_del_hmap(t_hmap **hmap)
{
	ft_del_arr(&((*hmap)->arr));
	ft_memdel((void **)hmap);
}

t_hmap	*ft_create_hashmap(int (*func_hash)(void *), t_ilist *list)
{
	t_hmap	*hmap;

	if (!func_hash || !list)
		return (NULL);
	if (!(hmap = ft_memalloc(sizeof(t_hmap))))
		return (NULL);
	hmap->func_hash = func_hash;
	ft_memcpy((void *)&hmap->list, (void *)list, sizeof(t_ilist));
	hmap->max_load = HASHMAP_FIRST_COUNT * HASHMAP_LOAD;
	hmap->arr = ft_create_arr_of_elems((void *)hmap->list.mem, hmap->list.size, HASHMAP_FIRST_COUNT, hmap->list.del);
	if (!hmap->arr)
		ft_memdel((void **)&hmap);
	return (hmap);
}
