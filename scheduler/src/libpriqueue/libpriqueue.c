/** @file libpriqueue.c
 */

#include <stdlib.h>
#include <stdio.h>

#include "libpriqueue.h"

// static node* make_nodes(void* ptr)
// {
// 	node* new_node = (node*) malloc(sizeof(node));
// 	new_node->process = ptr;
// 	new_node->next = NULL;
// 	return new_node;
// }
/**
  Initializes the priqueue_t data structure.

  Assumtions
    - You may assume this function will only be called once per instance of priqueue_t
    - You may assume this function will be the first function called using an instance of priqueue_t.
  @param q a pointer to an instance of the priqueue_t data structure
  @param comparer a function pointer that compares two elements.
  See also @ref comparer-page
 */
void priqueue_init(priqueue_t *q, int(*comparer)(const void *, const void *))
{
	q->comp = comparer;
	q->size = 0;
	q->head = NULL;
}


/**
  Inserts the specified element into this priority queue.

  @param q a pointer to an instance of the priqueue_t data structure
  @param ptr a pointer to the data to be inserted into the priority queue
  @return The zero-based index where ptr is stored in the priority queue,
	where 0 indicates that ptr was stored at the front of the priority queue.
 */
int priqueue_offer(priqueue_t *q, void *ptr)
{
	node n_node = malloc(sizeof(node));
  n_node->process = ptr;
  n_node->next = NULL;
  if(q->size == 0)
  {
    q->head = n_node;
		q->size++;
		return 0;
  }

	temp = q->head;
  previous = NULL;

  int location = 0;
  while(temp != NULL && q->comp(temp->process,ptr) < 0)
  {
    previous = temp;
    temp = temp->next;
    location++;
  }
  if(location == 0)
  {
    q->size++;
    n_node->next = q->head;
    q->head = n_node;
    return 0;
  }

  previous->next = n_node;
  n_node->next = temp;

  q->size++;
	return location;
}


/**
  Retrieves, but does not remove, the head of this queue, returning NULL if
  this queue is empty.

  @param q a pointer to an instance of the priqueue_t data structure
  @return pointer to element at the head of the queue
  @return NULL if the queue is empty
 */
void *priqueue_peek(priqueue_t *q)
{
	if(q->size == 0)
	{
		return NULL;
	}
	else
	{
		return q->head->process;
	}
}


/**
  Retrieves and removes the head of this queue, or NULL if this queue
  is empty.

  @param q a pointer to an instance of the priqueue_t data structure
  @return the head of this queue
  @return NULL if this queue is empty
 */
void *priqueue_poll(priqueue_t *q)
{
	if(q->size == 0)
	{
		return NULL;
	}
	temp = q->head;
	void* return_process = NULL;

	if (temp != NULL){
		q->head = temp->next;
	}
	else {
		q->head = NULL;
	}
	return_process = temp->process;
	free(temp);
	q->size--;
	return return_process;
	/*else{
		temp = q->head;
		void* return_process = temp->process;
		q->head = temp->next;
		q->size--;
		free(temp);
		return return_process;
	}*/
		// this node might need to be freed, to solve it I would create an accessor
		// function to get the value and free it.
}


/**
  Returns the element at the specified position in this list, or NULL if
  the queue does not contain an index'th element.

  @param q a pointer to an instance of the priqueue_t data structure
  @param index position of retrieved element
  @return the index'th element in the queue
  @return NULL if the queue does not contain the index'th element
 */
void *priqueue_at(priqueue_t *q, int index)
{
	if(index >= q->size)
	{
		return NULL;
	}
	else
	{
		temp = q->head;
		int tracker = 1;
		while(tracker <= index)
		{
			temp = temp->next;
			tracker++;
		}
		/*if (index == tracker)
			return temp;
		else
			return NULL;*/
		return temp->process;
	}
}


/**
  Removes all instances of ptr from the queue.

  This function should not use the comparer function,
	but check if the data contained in each element of the queue is equal (==) to ptr.

  @param q a pointer to an instance of the priqueue_t data structure
  @param ptr address of element to be removed
  @return the number of entries removed
 */
int priqueue_remove(priqueue_t *q, void *ptr)
{
	int num_deleted = 0;
	if (q->size == 0)
		return 0;
	temp = q->head;
	if(q->comp(ptr, temp->process) == 0){
		q->head = temp->next;
		free(temp);
		q->size--;
		return priqueue_remove(q, ptr) + 1;
	}

	current = temp->next;
	previous = temp;

	while (current != NULL) {
		if(q->comp(current->process, ptr) == 0){
			num_deleted++;
			temp = current->next;
			previous->next = temp;
			free(current);
			current = temp;
			q->size--;
			}
		else{
			previous = current;
			current = current->next;
		}
	}
	return num_deleted;
				/*else
	{
		while(q->head->process == ptr)
		{
			priqueue_poll(q);
			num_deleted++;
		}
		current = q->head;
		while(current != NULL)
		{
			temp = current ->next;
			if(temp->process == ptr)
			{
				current->next = temp -> next;
				free(temp);
				q->size--;
				num_deleted++;
			}
			current = current->next;
		}*/
//	}//end while
		//return num_deleted;
}



/**
  Removes the specified index from the queue, moving later elements up
  a spot in the queue to fill the gap.

  @param q a pointer to an instance of the priqueue_t data structure
  @param index position of element to be removed
  @return the element removed from the queue
  @return NULL if the specified index does not exist
 */
void *priqueue_remove_at(priqueue_t *q, int index)
{
	if(index < 0 || index > q->size)
	{
		return NULL;
	}
	//I do not really think it is a good way to do it, remember how to delete elem in linkedlist
	node delEle = q->head;
	//previous = current;
	int tracker = 0;
	while(tracker < index)
	{
		current = delEle;
		delEle = delEle->next;
		tracker++;
	}
	void* process_deleted = delEle->process;
	current = delEle -> next;
	free(delEle);
	q->size--;
	return process_deleted;
}


/**
  Returns the number of elements in the queue.

  @param q a pointer to an instance of the priqueue_t data structure
  @return the number of elements in the queue
 */
int priqueue_size(priqueue_t *q)
{
	return q->size;
}


/**
  Destroys and frees all the memory associated with q.

  @param q a pointer to an instance of the priqueue_t data structure
 */
void priqueue_destroy(priqueue_t *q)
{
	current = q->head;
	//previous = q->head;
	while(q->size > 0)
	{
		temp = current->next;
		free(current);
		current = temp;
		q->size--;
	}
	q->head = NULL;
}
