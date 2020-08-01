/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tnode_track.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:12:06 by ssoraka           #+#    #+#             */
/*   Updated: 2020/01/12 18:12:06 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collections_header.h"
#include "collections_help_header.h"

/*
** надо исправить эту функцию
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

void	ft_rbtree_prefix(t_rbtr *tree,
		void (*func)(void *, void *), void *param)
{
	if (tree->root.left)
		ft_tnode_prefix(tree->root.left, func, param);
}

void	ft_rbtree_postfix(t_rbtr *tree,
		void (*func)(void *, void *), void *param)
{
	if (tree->root.left)
		ft_tnode_postfix(tree->root.left, func, param);
}

void	ft_rbtree_infix(t_rbtr *tree,
		void (*func)(void *, void *), void *param)
{
	if (tree->root.left)
		ft_tnode_infix(tree->root.left, func, param);
}
