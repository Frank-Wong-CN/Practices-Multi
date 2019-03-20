#include "common_ds.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int queue_init(Queue **queue)
{
	if (queue == NULL)
	{
		errno = EINVAL;
		return errno;
	}
	
	*queue = (Queue *)malloc(sizeof(Queue));
	if (*queue == NULL)
		return errno;
	memset(*queue, 0, sizeof(Queue));
	
	return llist_init(&((*queue)->list));
}

int queue_enqueue(Queue *queue, void *data)
{
	if (queue == NULL || queue->list == NULL || data == NULL)
	{
		errno = EINVAL;
		return errno;
	}
	
	return llist_insert(queue->list, data, queue->list->length);
}

int queue_peek(Queue *queue, void **data, void (*data_copier)(void **, const void *))
{
	if (queue == NULL || queue->list == NULL || data == NULL || data_copier == NULL || queue->list->length == 0)
	{
		errno = EINVAL;
		return errno;
	}
	
	void *src = NULL;
	int retval = llist_get(queue->list, 0, &src);
	if (retval != 0)
		return retval;
	
	data_copier(data, src);
	
	return 0;
}

int queue_dequeue(Queue *queue, void **data)
{
	if (queue == NULL || queue->list == NULL || data == NULL || queue->list->length == 0)
	{
		errno = EINVAL;
		return errno;
	}
	
	int retval = 0;
	
	retval = llist_get(queue->list, 0, data);
	if (retval != 0)
		return retval;
	
	retval = llist_remove(queue->list, 0, NULL, NULL);
	if (retval != 0)
		return retval;
	
	return 0;
}

int queue_size(Queue *queue)
{
	if (queue == NULL || queue->list == NULL)
		return -1;
	
	return queue->list->length;
}

int queue_destroy(Queue **queue, void (*data_destroyer)(void **))
{
	if (queue == NULL || *queue == NULL || (*queue)->list == NULL)
	{
		errno = EINVAL;
		return errno;
	}
	
	return llist_destroy(&((*queue)->list), data_destroyer);
}

