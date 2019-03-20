#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "common_ds.h"
#include "simple_tree.h"

static int index = 0;
static const int size = 3;

int fact(int num)
{
	if (num == 1 || num == 0)
		return 1;

	return num * fact(num - 1);
}

int walker(void *num)
{
	printf("%d ", (int) num);
	return 0;
}

int arrange(LinkedList *list)
{
	printf("%d: ", index++);
	llist_walk(list, walker);
	printf("\n");

	return 0;
}

int llist_part_reverse(LinkedList *list, int start, int end)
{
	if (list == NULL || start < 0 || start > list->length || end < 0 || end > list->length)
		return (errno = EINVAL, errno);
	
	while (start < end)
		llist_swap(list, start++, end--);
	
	return 0;
}

int llist_clone(LinkedList *src, LinkedList **dst)
{
	if (src == NULL || dst == NULL || *dst != NULL)
		return (errno = EINVAL, errno);
	
	LinkedList *tmp = NULL;
	tmp = (LinkedList *)malloc(sizeof(LinkedList));
	memset(tmp, 0, sizeof(LinkedList));
	
	llist_init(&tmp);
	
	void *recv = NULL;
	for (int i = 0; i < src->length; i++)
	{
		llist_get(src, i, &recv);
		llist_insert(tmp, recv, i);
	}
	
	*dst = tmp;
	
	return 0;
}

int build_tree(Tree* tree, int size, LinkedList *list, int level)
{
	int rv = 0; //Unused
	if (size > 2)
	{
		for (int i = 0; i < size; i++)
		{
			//Add child nodes
			Tree *child = NULL;
			tree_init(&child);
			llist_insert(tree->childs, (void *) child, ~(1 << 31));
			
			//Feed data to each child nodes
			LinkedList *curNode = NULL;
			llist_clone(list, &curNode);
			child->data = curNode;
			llist_part_reverse(curNode, level, level + i);
			
			//Build sub-trees
			build_tree(child, size - 1, curNode, level + 1);
		}
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			//Add child nodes
			Tree *child = NULL;
			tree_init(&child);
			llist_insert(tree->childs, (void *) child, ~(1 << 31));
			
			//Feed data to each child nodes
			LinkedList *curNode = NULL;
			llist_clone(list, &curNode);
			child->data = curNode;
			llist_part_reverse(curNode, level, level + i);
		}
	}
	
	return 0;
}

int main(int argc, char *argv[])
{
	Tree *root = NULL;
	tree_init(&root);

	LinkedList *list = NULL;
	llist_init(&list);

	for (int i = 0; i <= size; i++)
		llist_insert(list, (void *) i, ~(1 << 31));
	
	build_tree(root, size, list, 0);
	
	tree_traverse_leaves(root, arrange);
}
