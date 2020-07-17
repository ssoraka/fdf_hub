
#include "collections_header.h"

void	ft_init_rbtree(t_rbtr *tree, int (*func_cmp)(t_old_key *, t_new_key *), void (*func_del)(t_old_key *, t_old_elem *))
{
	if (tree)
	{
		tree->func_cmp = func_cmp;
		tree->func_del = func_del;
	}
}

t_rbtr	*ft_create_rbtree(int (*func_cmp)(t_old_key *, t_new_key *), void (*func_del)(t_old_key *, t_old_elem *))
{
	t_rbtr	*tree;

	if (!func_cmp)
		return (NULL);
	tree = ft_memalloc(sizeof(t_rbtr));
	ft_init_rbtree(tree, func_cmp, func_del);
	return (tree);
}

void	ft_del_rbtree_nodes(t_rbtr *tree)
{
	if (tree->root.left)
		ft_tnode_del_all(tree->root.left, tree->func_del);
}

void	ft_del_rbtree(t_rbtr **tree)
{
	ft_del_rbtree_nodes(*tree);
	ft_memdel((void **)tree);
}

void	ft_rbtree_insert(t_rbtr *tree, t_tnode *node)
{
	t_tnode *tmp;
	t_tnode **current;

	if (!tree || !node)
		return ;
	tmp = &tree->root;
	current = &tmp->left;
	while (*current)
	{
		tmp = *current;
		if (tree->func_cmp(tmp->key, node->key) >= 0)
			current = &tmp->right;
		else
			current = &tmp->left;
	}
	*current = node;
	node->parent = tmp;
	(tree->elems_count)++;
}
 /*
 нужно получить хэш из ключа, поместить его в ноду
 для предотвращения повторных вычислений,
 вроде хеш нужен только для определения ячейки к хеш мапе
 и вроде он нафиг больше не нужен
 */
t_bool	ft_rbtree_add(t_rbtr *tree, void *key, void *value)
{
	t_tnode *node;

	if (!tree || !value)
		return (FALSE);
	if (!(node = ft_create_tnode(key, value)))
		return (FALSE);
	ft_rbtree_insert(tree, node);
	ft_tnode_rebalance(node);
	return (TRUE);
}

void	*ft_rbtree_get_elem(t_rbtr *tree, void *key)
{
	t_tnode	*node;
	int		cmp;

	if (!tree || !key)
		return (NULL);
	node = tree->root.left;
	while (node)
	{
		cmp = tree->func_cmp(node->key, key);
		if (!cmp)
			return (node->elem);
		else if (cmp > 0)
			node = node->right;
		else
			node = node->left;
	}
	return (NULL);
}

/*
 * надо исправить эту функцию
 */
void	*ft_rbtree_get_next(t_rbtr *tree)
{
	if (!tree || !tree->elems_count)
		return (NULL);
	if (!tree->next)
		tree->next = ft_find_left_value(tree->root.left);
	else if (tree->next->right)
	{
		tree->next = tree->next->right;
		tree->next = ft_find_left_value(tree->next);
	}
	else if (tree->next->parent != &tree->root
	&& tree->next == tree->next->parent->left)
		tree->next = tree->next->parent;
	else if ((tree->next = tree->next->parent->right))
	{
		while (tree->next != tree->next->parent->left)
			tree->next = tree->next->parent;
		if (tree->next->parent == &tree->root)
			tree->next = NULL;
		else
			tree->next = tree->next->parent;
	}
	if (tree->next)
		return (tree->next->elem);
	return (NULL);
}

void	ft_rbtree_prefix(t_rbtr *tree, void (*func)(void *, void *), void *param)
{
	if (tree->root.left)
		ft_tnode_prefix(tree->root.left, func, param);
}

void	ft_rbtree_postfix(t_rbtr *tree, void (*func)(void *, void *), void *param)
{
	if (tree->root.left)
		ft_tnode_postfix(tree->root.left, func, param);
}

void	ft_rbtree_infix(t_rbtr *tree, void (*func)(void *, void *), void *param)
{
	if (tree->root.left)
		ft_tnode_infix(tree->root.left, func, param);
}
