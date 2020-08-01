/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collections_struct.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 20:59:39 by ssoraka           #+#    #+#             */
/*   Updated: 2019/04/19 13:13:30 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COLLECTIONS_STRUCT_H
# define FT_COLLECTIONS_STRUCT_H
# include "collections_header.h"

# define RED 0
# define BLACK 1

# define MAX_LIST_SIZE 128

typedef void	t_new_elem;
typedef void	t_old_elem;
typedef void	t_new_key;
typedef void	t_old_key;
typedef int		t_bool;

typedef struct		s_arr
{
	void			*elems;
	char			*current;
	size_t			next;
	size_t			elems_count;
	int				elems_used;
	int				elem_size;
	void			(*func_del)(void *);
	void			*(*value)(void *);
}					t_arr;

typedef struct		s_lnode
{
	void			*elem;
	struct s_lnode	*next;
	struct s_lnode	*prev;
}					t_lnode;

typedef struct		s_llist
{
	struct s_lnode	start;
	struct s_lnode	end;
	struct s_lnode	*current;
	size_t			elems_count;
	void			(*func_del)(void *);
}					t_llist;

typedef struct		s_ilist
{
	char			mem[MAX_LIST_SIZE];
	int				(*add)(void *, void *, void *);
	void			*(*find)(void *, void *);
	void			(*del)(void *);
	int				(*get_next)(void *, void **, void **);
	void			(*del_list_without_key_value)(void *);
	int				size;
}					t_ilist;

typedef struct		s_hmap
{
	struct s_ilist	list;
	struct s_arr	*arr;
	int				(*func_hash)(void *);
	int				elems_count;
	int				elems_used;
	int				max_load;
}					t_hmap;

typedef struct		s_tnode
{
	void			*elem;
	void			*key;
	struct s_tnode	*parent;
	struct s_tnode	*right;
	struct s_tnode	*left;
	int				color;
}					t_tnode;

typedef struct		s_rbtr
{
	struct s_tnode	root;
	struct s_tnode	*next;
	int				(*func_cmp)(t_old_key *, t_new_key *);
	void			(*func_del)(t_old_key *, t_old_elem *);
	int				elems_count;
}					t_rbtr;

#endif
