#ifndef _COMMON_DATA_STRUCTURE_H_
#define _COMMON_DATA_STRUCTURE_H_

typedef struct _Elem
{
	struct _Elem *next;
	void *data;
} Elem;

typedef struct _LinkedList
{
	Elem* head;
	Elem* tail;
	unsigned int length;
} LinkedList;

typedef struct _SeqList
{
	void** elements;
	unsigned int length;
} SeqList;

typedef struct _Queue
{
	LinkedList* list;
} Queue;

typedef struct _Stack
{
	LinkedList* list;
} Stack;

//Element functions
int elem_init(Elem **); //Allocate buffer for a ds element
int elem_destroy(Elem **); //Free the buffer of a ds element

//Linked list functions
int llist_init(LinkedList **); //Allocate buffer for a list
int llist_insert(LinkedList *, void *, int); //This function will automatically allocate buffer for inserting element
int llist_remove(LinkedList *, int, void **, void(*)(void **, const void *)); //Free the previously allocated buffer, and copy the data to the third argument, is it is not NULL
int llist_get(LinkedList *, int, void **); //Acquire the pointer to the element inside the list
int llist_walk(LinkedList *, int(*)(void *)); //Execute a function for each element
int llist_exists(LinkedList *, void *, int(*)(const void *, const void *)); //Compare two elements to check if the element exists
int llist_size(LinkedList *); //Get the size of the list
int llist_swap(LinkedList *, int, int); //Swap the two element
int llist_destroy(LinkedList **, void(*)(void **)); //Free all elements and the list buffer, the second argument is the cleanup function for each element

//Sequence list functions
//Not implemented, yet

//Queue funcitons
int queue_init(Queue **); //Allocate buffer for a queue
int queue_enqueue(Queue *, void *); //Enqueue an element
int queue_peek(Queue *, void **, void(*)(void **, const void *)); //Acquire a copy of the next element
int queue_dequeue(Queue *, void **); //Dequeue an element
int queue_size(Queue *); //Get the size of the queue
int queue_destroy(Queue **, void(*)(void **)); //Free all elements and the queue buffer

//Stack functions
int stack_init(Stack **); //Allocate buffer for a stack
int stack_push(Stack *, void *); //Push an element
int stack_peek(Stack *, void **, void(*)(void **, const void *)); //Acquire a copy of the next element
int stack_pop(Stack *, void **); //Pop an element
int stack_size(Stack *); //Get the size of the stack
int stack_destroy(Stack **, void(*)(void **)); //Free all elements and the stack buffer

#endif
