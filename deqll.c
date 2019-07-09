
// NOTE: ALL double ended queue parameters must be valid

#include "deqll.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// DO NOT MODIFY THIS STRUCTURE
struct dllnode {
  double item;
  struct dllnode *prev;
  struct dllnode *next;
};

// DO NOT MODIFY THIS STRUCTURE
struct dequeue {
  struct dllnode *front;
  struct dllnode *back;
};

// dequeue_create() creates a new empty queue
// effects: allocates memory (client must call dequeue_destroy)
struct dequeue *dequeue_create(void) {
  struct dequeue *q = malloc(sizeof(struct dequeue));
  q->front = NULL; // set null pointers
  q->back = NULL; // set null pointers
  return q;
}

// dequeue_is_empty(q) determines if double ended queue q is empty
// time: O(1)
bool dequeue_is_empty(const struct dequeue *q) {
  return q->front == NULL; // check whether the front is null or not
}

// dequeue_front(q) returns the front item in the double ended queue q
// requires: double ended queue is not empty
// time: O(1)
double dequeue_front(const struct dequeue *q) {
  assert(q->front);// check whether the front pointer is null or not
  assert(!dequeue_is_empty(q));
  return q->front->item; // return the item
}

// dequeue_back(q) returns the back item in the double ended queue q
// requires: double ended queue is not empty
// time: O(1)
double dequeue_back(const struct dequeue *q) {
  assert(q->back); //check whether the back pointer is null or not
  assert(!dequeue_is_empty(q));
  return q->back->item; // return the item
}

// dequeue_remove_front(q) returns and removes the front item from q
// requires: double ended queue is not empty
// effects: modifies q
// time: O(1)
double dequeue_remove_front(struct dequeue *q) {
  //assert(q->front);
  if(q->front == NULL) return 8192;
  double retval = q->front->item; // return value
  struct dllnode *backup = q->front; // to free create dummy pointer
  q->front = q->front->next; // iterate
  if(q->front != NULL){
    q->front->prev = NULL;
  }else{
    q->back = NULL;
  }
  
  free(backup);
  
  return retval;
}

// dequeue_remove_back(q) returns and removes the back item from q
// requires: double ended queue is not empty
// effects: modifies q
// time: O(1)
double dequeue_remove_back(struct dequeue *q) {
  assert(q->back);
  assert(!dequeue_is_empty(q));
  double retval = q->back->item;
  // dummy pointer to free
  struct dllnode *backup = q->back;
  // remove the last one
  q->back = q->back->prev;
  if( q->back != NULL){
    q->back->next = NULL;
  }else{
    q->front = NULL;
  }
  free(backup);
  
  return retval;
}

// dequeue_add_front(item, q) adds item to the front of q
// effects: modifies q
// time: O(1)
void dequeue_add_front(double item, struct dequeue *q) {
  // create the node that will be added
  struct dllnode *node = malloc(sizeof(struct dllnode));
  node->item = item;
  node->next = NULL;
  node->prev = NULL;
  // add
  if (q->front == NULL) {
  q->back = node;
  } else {
  q->front->prev = node;
  node->next = q->front;
  }
  q->front = node;
}

// dequeue_add_back(item, q) adds item to the back of queue q
// effects: modifies q
// time: O(1)
void dequeue_add_back(double item, struct dequeue *q){
  // create the node that will be added
  struct dllnode *node = malloc(sizeof(struct dllnode));
  node->item = item;
  node->next = NULL;
  node->prev = NULL;
  // add
  if (q->front == NULL) {
  q->front = node;
  } else {
  node->prev = q->back;
  q->back->next = node;
  }
  q->back = node;
}

// dequeue_destroy(q) frees all memory for q
// requires: q must be from a previous malloc
// effects: q is no longer valid
void dequeue_destroy(struct dequeue *q) {
  // kill all items
  while (!dequeue_is_empty(q)) {
    dequeue_remove_front(q);
  }
  // kil the wrapper
  free(q);
}

// DO NOT MODIFY THIS FUNCTION
// dequeue_print(q) prints the contents of q
// effects: prints to output
void dequeue_print(const struct dequeue *q) {
  struct dllnode *temp = q->front;

  while (temp) {
    printf("%f\n", temp->item);
    temp = temp->next;
  }

  

}

double *deq_to_array(const struct dequeue *q){
    double a[800];
    struct dllnode *temp = q->front;
    int i = 0;
    while (temp) {
        a[i] = temp->item;
        temp = temp->next;

        i++;
    }
    printf("NUMBER_OF_ELEMENTS %d\n", i);
    return a;
}
