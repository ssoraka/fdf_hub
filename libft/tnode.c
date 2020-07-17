
#include "collections_header.h"

t_tnode *ft_create_tnode(void *key, void *value)
{
	t_tnode *node;

	node = ft_memalloc(sizeof(t_tnode));
	if (node)
	{
		node->elem = value;
		node->key = key;
		node->color = RED;
	}
	return (node);
}

int		ft_is_red_color(t_tnode *node)
{
	if (!node || node->color == BLACK)
		return (FALSE);
	return (TRUE);
}

int		ft_is_right_child(t_tnode *node)
{
	if (node == node->parent->right)
		return (TRUE);
	return (FALSE);
}

t_tnode *ft_get_uncle(t_tnode *node)
{
	t_tnode *grant;

	if (!node || !node->parent || !(grant = node->parent->parent))
		return (NULL);
	if (node->parent == grant->left)
		return (grant->right);
	else
		return (grant->left);
}


void	ft_tnode_left_rotate(t_tnode *node)
{
	t_tnode *grant;
	t_tnode *tmp;

	if (!(grant = node->parent->parent))
		return ;
	tmp = node->parent;
	if (grant->right == tmp)
		grant->right = node;
	else
		grant->left = node;
	node->parent = grant;
	tmp->right = node->left;
	if (node->left)
		node->left->parent = tmp;
	node->left = tmp;
	tmp->parent = node;
}

void	ft_tnode_right_rotate(t_tnode *node)
{
	t_tnode *grant;
	t_tnode *tmp;

	if (!(grant = node->parent->parent))
		return ;
	tmp = node->parent;
	if (grant->right == tmp)
		grant->right = node;
	else
		grant->left = node;
	node->parent = grant;
	tmp->left = node->right;
	if (node->right)
		node->right->parent = tmp;
	node->right = tmp;
	tmp->parent = node;
}

void	ft_case_red_dad_red_uncle(t_tnode *node)
{
	 node->parent->color = BLACK;
	 ft_get_uncle(node)->color = BLACK;
	 node->parent->parent->color = RED;
	 ft_tnode_rebalance(node->parent->parent);
}

void	ft_case_red_right_dad_and_black_left_uncle(t_tnode *node)
{
	if (node->parent->right == node)
	{
		node->parent->color = BLACK;
		node->parent->parent->color = RED;
		ft_tnode_left_rotate(node->parent);
	}
	else
	{
		ft_tnode_right_rotate(node);
		ft_case_red_right_dad_and_black_left_uncle(node->right);
	}
}

void	ft_case_red_left_dad_and_black_right_uncle(t_tnode *node)
{
	if (node->parent->left == node)
	{
		node->parent->color = BLACK;
		node->parent->parent->color = RED;
		ft_tnode_right_rotate(node->parent);
	}
	else
	{
		ft_tnode_left_rotate(node);
		ft_case_red_left_dad_and_black_right_uncle(node->left);
	}
}

void	ft_tnode_rebalance(t_tnode *node)
{
	if (!node || !node->parent)
		return ;
	else if (!node->parent->parent)
		node->color = BLACK;
	else if (node->color == RED && node->parent->color == RED)
	{
		if (ft_is_red_color(ft_get_uncle(node)))
			ft_case_red_dad_red_uncle(node);
		else if (ft_is_right_child(node->parent))
			ft_case_red_right_dad_and_black_left_uncle(node);
		else
			ft_case_red_left_dad_and_black_right_uncle(node);
	}
}

t_tnode	*ft_find_left_value(t_tnode *node)
{
	while (node->left)
		node = node->left;
	return (node);
}

void	ft_tnode_infix(t_tnode *node, void (*func)(void *, void *), void *param)
{
	if (node->left)
		ft_tnode_infix(node->left, func, param);
	func(node->elem, param);
	if (node->right)
		ft_tnode_infix(node->right, func, param);
}

void	ft_tnode_postfix(t_tnode *node, void (*func)(void *, void *), void *param)
{
	if (node->right)
		ft_tnode_postfix(node->right, func, param);
	func(node->elem, param);
	if (node->left)
		ft_tnode_postfix(node->left, func, param);
}

void	ft_tnode_prefix(t_tnode *node, void (*func)(void *, void *), void *param)
{
	func(node->elem, param);
	if (node->left)
		ft_tnode_prefix(node->left, func, param);
	if (node->right)
		ft_tnode_prefix(node->right, func, param);
}

void	ft_tnode_del(t_tnode *node, void (*func)(void *, void *))
{
	if (func && node->elem)
		func(node->key, node->elem);
	free(node);
}

void	ft_tnode_del_all(t_tnode *node, void (*func)(void *, void *))
{
	if (node->left)
		ft_tnode_del_all(node->left, func);
	if (node->right)
		ft_tnode_del_all(node->right, func);
	ft_tnode_del(node, func);
}
