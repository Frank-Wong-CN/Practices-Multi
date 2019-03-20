#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "common_ds.h"
#include "simple_tree.h"

int tree_init(Tree **tree)
{
	if (tree == NULL || *tree != NULL)
		return (errno = EINVAL, errno);

	Tree *tmp = NULL;
	tmp = (Tree *)malloc(sizeof(Tree));
	memset(tmp, 0, sizeof(Tree));

	llist_init(&(tmp->childs));

	*tree = tmp;
	return 0;
}

int tree_destroy(Tree **tree)
{
	if (tree == NULL || *tree == NULL)
		return (errno = EINVAL, errno);
	
	Tree *tmp = *tree;
	llist_destroy(&(tmp->childs), (void (*)(void **)) tree_destroy);

	//Manually destroy the data before the pointers went wild

	free(tmp);
	*tree = NULL;

	return 0;
}

int tree_childs_walk(Tree *tree, int (*traverse)(Tree *, void (*)(void *)), void (*function)(void *))
{
	if (tree == NULL || traverse == NULL || function == NULL)
	{
		errno = EINVAL;
		return errno;
	}
	
	LinkedList *list = tree->childs;
	int retval = 0;
	int position = list->length;
	Elem *cur_elem = list->head;

	while (position > 0 && cur_elem != NULL)
	{
		retval = traverse(cur_elem->data, function);
		if (retval != 0)
			return retval;
		cur_elem = cur_elem->next;
		position -= 1;
	}
	
	return 0;
}

int tree_traverse_leaves(Tree *tree, void (*function)(void *))
{
	if (tree == NULL || function == NULL)
		return (errno = EINVAL, errno);

	if (llist_size(tree->childs) == 0)
	{
		function(tree->data);
		return 0;
	}
	else
	{
		return tree_childs_walk(tree, tree_traverse_leaves, function);
	}
}
