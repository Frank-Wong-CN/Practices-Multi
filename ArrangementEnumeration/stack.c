#include "common_ds.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int stack_init(Stack **stack)
{
	if (stack == NULL)
	{
		errno = EINVAL;
		return errno;
	}
	
	*stack = (Stack *)malloc(sizeof(Stack));
	if (*stack == NULL)
		return errno;
	memset(*stack, 0, sizeof(Stack));
	
	return llist_init(&((*stack)->list));
}

int stack_push(Stack *stack, void *data)
{
	if (stack == NULL || stack->list == NULL || data == NULL)
	{
		errno = EINVAL;
		return errno;
	}
	
	return llist_insert(stack->list, data, stack->list->length);
}

int stack_peek(Stack *stack, void **data, void (*data_copier)(void **, const void *))
{
	if (stack == NULL || stack->list == NULL || data == NULL || data_copier == NULL || stack->list->length == 0)
	{
		errno = EINVAL;
		return errno;
	}
	
	void *src = NULL;
	int retval = llist_get(stack->list, stack->list->length - 1, &src);
	if (retval != 0)
		return retval;
	
	data_copier(data, src);
	
	return 0;
}

int stack_pop(Stack *stack, void **data)
{
	if (stack == NULL || stack->list == NULL || data == NULL || stack->list->length == 0)
	{
		errno = EINVAL;
		return errno;
	}
	
	int retval = 0;
	
	retval = llist_get(stack->list, stack->list->length - 1, data);
	if (retval != 0)
		return retval;
	
	retval = llist_remove(stack->list, stack->list->length - 1, NULL, NULL);
	if (retval != 0)
		return retval;
	
	return 0;
}

int stack_size(Stack *stack)
{
	if (stack == NULL || stack->list == NULL)
		return -1;
	
	return stack->list->length;
}

int stack_destroy(Stack **stack, void (*data_destroyer)(void **))
{
	if (stack == NULL || *stack == NULL || (*stack)->list == NULL)
	{
		errno = EINVAL;
		return errno;
	}
	
	return llist_destroy(&((*stack)->list), data_destroyer);
}

