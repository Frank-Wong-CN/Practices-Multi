#ifndef _SIMPLE_TREE_H_
#define _SIMPLE_TREE_H_

#include "common_ds.h"

typedef struct _Tree
{
	LinkedList *childs;
	void *data;
} Tree;

int tree_init(Tree **tree);
int tree_destroy(Tree **tree);
int tree_childs_walk(Tree *tree, int (*traverse)(Tree *, void (*)(void *)), void (*function)(void *));
int tree_traverse_leaves(Tree *tree, void (*function)(void *));

#endif