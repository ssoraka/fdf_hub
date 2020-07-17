
#include "libft.h"
#include "collections_header.h"

void	ft_ilist_set_add(t_ilist *ilist, int (*add)(void *, void *, void *))
{
	ilist->add = add;
}

void	ft_ilist_set_get(t_ilist *ilist, void *(*find)(void *, void *))
{
	ilist->find = find;
}

void	ft_ilist_set_del(t_ilist *ilist, void (*del)(void *))
{
	ilist->del = del;
}

void	ft_ilist_set_get_next(t_ilist *list, int (*get_next)(void *, void **, void **))
{
	list->get_next = get_next;
}

void	ft_ilist_set_func_for_resize_map(t_ilist *list, void (*del_list_without_key_value)(void *))
{
	list->del_list_without_key_value = del_list_without_key_value;
}

void	ft_ilist_set_list(t_ilist *ilist, void *list, int elem_size)
{
	if (elem_size <= MAX_LIST_SIZE && elem_size > 0)
	{
		ft_memcpy((void *)ilist->mem, list, elem_size);
		ilist->size = elem_size;
	}
	else
	{
		ft_bzero((void *)ilist->mem, MAX_LIST_SIZE);
		ilist->size = 0;
	}
}
