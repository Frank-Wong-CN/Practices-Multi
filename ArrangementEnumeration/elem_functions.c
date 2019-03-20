#include "common_ds.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int elem_init(Elem **elem)
{
	if (elem == NULL)
	{
		errno = EINVAL;
		return errno;
	}
	
	*elem = (Elem *)malloc(sizeof(Elem));
	if (*elem == NULL)
		return errno;
	memset(*elem, 0, sizeof(Elem));
	
	return 0;
}

int elem_destroy(Elem **elem)
{
	if (elem == NULL || *elem == NULL)
	{
		errno = EINVAL;
		return errno;
	}
	
	free(*elem);
	*elem = NULL;
	
	return 0;
}
