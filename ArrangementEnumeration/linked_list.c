#include "common_ds.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

//DECLARATIONS FOR PRIVATE FUNCTIONS
int llist_set(LinkedList *, int, void *); //Set the element directly by index, DANGEROUS for causing memory leak

int llist_init(LinkedList **list)
{
	if (list == NULL)
	{
		errno = EINVAL;
		return errno;
	}
	
	*list = (LinkedList *)malloc(sizeof(LinkedList));
	if (*list == NULL)
		return errno;
	memset(*list, 0, sizeof(LinkedList));
	
	return 0;
}

int llist_insert(LinkedList *list, void *data, int position)
{
	if (list == NULL || data == NULL || position < 0)
	{
		errno = EINVAL;
		return errno;
	}
	
	int retval = 0;
	Elem *new_elem = NULL;
	
	retval = elem_init(&new_elem);
	if (retval != 0)
		return retval;
	new_elem->data = data;
	
	Elem *cur_elem = list->head;
	Elem *prev_elem = NULL;
	
	while (position > 0 && cur_elem != NULL)
	{
		prev_elem = cur_elem;
		cur_elem = cur_elem->next;
		position -= 1;
	}
	
	if (prev_elem == NULL)
		list->head = new_elem;
	else
		prev_elem->next = new_elem;
	
	if (cur_elem == NULL)
		list->tail = new_elem;
	else
		new_elem->next = cur_elem;
	
	list->length += 1;
	
	return 0;
}

int llist_remove(LinkedList *list, int position, void **data, void (*data_copier)(void **, const void *))
{
	if (list == NULL || position < 0 || (data != NULL && data_copier == NULL))
	{
		errno = EINVAL;
		return errno;
	}
	
	if (list->length == 0)
		return 0;
	
	Elem *cur_elem = list->head;
	Elem *prev_elem = NULL;
	
	while (position > 0 && cur_elem->next != NULL)
	{
		prev_elem = cur_elem;
		cur_elem = cur_elem->next;
		position -= 1;
	}
	
	if (data != NULL)
		data_copier(data, cur_elem->data);
	
	if (prev_elem == NULL)
		list->head = cur_elem->next;
	else
		prev_elem->next = cur_elem->next;
	
	if (cur_elem->next == NULL)
		list->tail = prev_elem;
	
	list->length -= 1;
	elem_destroy(&cur_elem);
	
	return 0;
}

int llist_get(LinkedList *list, int position, void **data)
{
	if (list == NULL || position < 0 || data == NULL || list->length == 0 || position > list->length - 1)
	{
		errno = EINVAL;
		return errno;
	}
	
	Elem *cur_elem = list->head;
	
	while (position > 0)
	{
		cur_elem = cur_elem->next;
		position -= 1;
	}
	
	*data = cur_elem->data;
	
	return 0;
}

int llist_walk(LinkedList *list, int (*function)(void *))
{
	if (list == NULL || function == NULL)
	{
		errno = EINVAL;
		return errno;
	}
	
	int retval = 0;
	int position = list->length;
	Elem *cur_elem = list->head;

	while (position > 0 && cur_elem != NULL)
	{
		retval = function(cur_elem->data);
		if (retval != 0)
			return retval;
		cur_elem = cur_elem->next;
		position -= 1;
	}
	
	return 0;
}

int llist_exists(LinkedList *list, void *data, int (*data_comparer)(const void *, const void *))
{
	if (list == NULL || data == NULL || data_comparer == NULL)
	{
		errno = EINVAL;
		return errno;
	}
	
	int position = list->length;
	Elem *cur_elem = list->head;

	while (position > 0 && cur_elem != NULL)
	{
		if (!data_comparer(data, cur_elem->data))
			return 1;
		cur_elem = cur_elem->next;
		position -= 1;
	}
	
	return 0;
}

int llist_size(LinkedList *list)
{
	if (list == NULL)
		return -1;
	
	return list->length;
}

int llist_swap(LinkedList *list, int a, int b)
{
	if (list == NULL)
	{
		errno = EINVAL;
		return errno;
	}
	
	if (a < 0 || a >= list->length || b < 0 || b >= list->length)
	{
		errno = EINVAL;
		return errno;
	}

	void *dataFromA = NULL;
	void *dataFromB = NULL;
	llist_get(list, a, &dataFromA);
	llist_get(list, b, &dataFromB);

	llist_set(list, a, dataFromB);
	llist_set(list, b, dataFromA);

	return 0;
}

int llist_destroy(LinkedList **list, void (*data_destroyer)(void **))
{
	if (list == NULL || *list == NULL)
	{
		errno = EINVAL;
		return errno;
	}
	
	int position = (*list)->length;
	Elem *cur_elem = (*list)->head;
	Elem *prev_elem = NULL;
	
	while (position > 0 && cur_elem != NULL)
	{
		if (data_destroyer != NULL)
			data_destroyer(&(cur_elem->data));
		
		prev_elem = cur_elem;
		cur_elem = cur_elem->next;
		
		elem_destroy(&prev_elem);
		position -= 1;
	}
	
	free(*list);
	*list = NULL;
	
	return 0;
}

int llist_set(LinkedList *list, int position, void *data)
{
	if (list == NULL || position < 0 || data == NULL || list->length == 0 || position > list->length - 1)
	{
		errno = EINVAL;
		return errno;
	}

	Elem *cur_elem = list->head;

	while (position > 0)
	{
		cur_elem = cur_elem->next;
		position -= 1;
	}

	cur_elem->data = data; //THIS WILL CAUSE MEMORY LEAK IF HANDLED UNCORRECTLY! ONLY USE IT WHEN EVERYTHING IS UNDER CONTROL

	return 0;
}
