
#include "collections_header.h"

void	ft_init_llist(t_llist *llist, void (*func_del)(void *))
{
	if (!llist)
		return ;
	llist->start.next = &llist->end;
	llist->start.prev = &llist->end;
	llist->end.next = &llist->start;
	llist->end.prev = &llist->start;
	llist->current = &llist->start;
	llist->func_del = func_del;
	llist->elems_count = 0;
}

t_llist	*ft_create_llist(void (*func_del)(void *))
{
	t_llist	*llist;

	llist = ft_memalloc(sizeof(t_llist));
	if (llist)
		ft_init_llist(llist, func_del);
	return (llist);
}

void	*ft_llist_get_next(t_llist *list)
{
	if (!list)
		return (NULL);
	list->current = list->current->next;
	if (list->current != &list->end)
		return (list->current->elem);
	list->current = &list->start;
	return (NULL);
}


int		ft_llist_dpush(t_llist *list, void *elem)
{
	t_lnode *node;

	if (!list)
		return (FALSE);
	if (!(node = ft_create_lnode(elem)))
		return (FALSE);
	ft_insert_lnode(node, list->end.prev);
	list->elems_count++;
	return (TRUE);
}
int		ft_llist_push(t_llist *list, void *elem)
{
	t_lnode *node;

	if (!list)
		return (FALSE);
	if (!(node = ft_create_lnode(elem)))
		return (FALSE);
	ft_insert_lnode(node, &list->start);
	list->elems_count++;
	return (TRUE);
}
void	*ft_llist_pop(t_llist *list)
{
	if (!list || !list->elems_count)
		return (NULL);
	list->elems_count--;
	return (ft_cut_lnode(list->start.next));
}
void	*ft_llist_dpop(t_llist *list)
{
	if (!list || !list->elems_count)
		return (NULL);
	list->elems_count--;
	return (ft_cut_lnode(list->end.prev));
}


int		ft_llist_add(t_llist *list, void *elem)
{
	return (ft_llist_dpush(list, elem));
}


void	ft_for_each_llist(t_llist *list, void (*func)(void *, void *), void *param)
{
	t_lnode *node;
	t_lnode *end;

	if (!func || !list)
		return ;
	node = list->start.next;
	end = &list->end;
	while (node != end)
	{
		func(node->elem, param);
		node = node->next;
	}
}

void	*ft_llist_get(t_llist *list, int num)
{
	t_lnode *node;

	if (!list)
		return (NULL);
	node = ft_lnode_get(num, list->elems_count, list->start.next, list->end.prev);
	if (node)
		return (node->elem);
	return (NULL);
}

void	ft_del_llist_elem(t_llist *list, int num)
{
	t_lnode *node;
	void *elem;

	if (!list)
		return ;
	node = ft_lnode_get(num, list->elems_count, list->start.next, list->end.prev);
	if (node)
	{
		elem = ft_cut_lnode(node);
		if (elem && list->func_del)
			list->func_del(elem);
		list->elems_count--;
	}
}

int		ft_insert_llist(t_llist *list, void *elem, int num)
{
	t_lnode *node;
	t_lnode *next;

	if (!list)
		return (FALSE);
	next = ft_lnode_get(num, list->elems_count, list->start.next, list->end.prev);
	if (!next)
		return (FALSE);
	if (!(node = ft_create_lnode(elem)))
		return (FALSE);
	ft_insert_lnode(node, next->prev);
	return (TRUE);
}

void	ft_del_llist(t_llist **list)
{
	void *elem;
	int i;
	t_llist *tmp;

	if (!list || !(*list))
		return ;
	tmp = *list;
	i = tmp->elems_count;
	while (i > 0)
	{
		elem = ft_cut_lnode(tmp->start.next);
		if (tmp->func_del)
			tmp->func_del(elem);
		i--;
	}
	ft_memdel((void **)list);
}
