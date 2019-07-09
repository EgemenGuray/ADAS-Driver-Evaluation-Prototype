#include <stdbool.h>

// a Double Ended Queue for ints
// NOTE: ALL double ended queue parameters must be valid

struct dequeue;

// dequeue_create() creates a new empty queue
// effects: allocates memory (client must call dequeue_destroy)
struct dequeue *dequeue_create(void);

// dequeue_is_empty(q) determines if double ended queue q is empty
// time: O(1)
bool dequeue_is_empty(const struct dequeue *q);

// dequeue_front(q) returns the front item in the double ended queue q
// requires: double ended queue is not empty
// time: O(1)
double dequeue_front(const struct dequeue *q);

// dequeue_back(q) returns the back item in the double ended queue q
// requires: double ended queue is not empty
// time: O(1)
double dequeue_back(const struct dequeue *q);

// dequeue_remove_front(q) returns and removes the front item from q
// requires: double ended queue is not empty
// effects: modifies q
// time: O(1)
double dequeue_remove_front(struct dequeue *q);

// dequeue_remove_back(q) returns and removes the back item from q
// requires: double ended queue is not empty
// effects: modifies q
// time: O(1)
double dequeue_remove_back(struct dequeue *q);

// dequeue_add_front(item, q) adds item to the front of q
// effects: modifies q
// time: O(1)
void dequeue_add_front(double item, struct dequeue *q);

// dequeue_add_back(item, q) adds item to the back of queue q
// effects: modifies q
// time: O(1)
void dequeue_add_back(double item, struct dequeue *q);

// dequeue_destroy(q) frees all memory for q
// requires: q must be from a previous malloc
// effects: q is no longer valid
void dequeue_destroy(struct dequeue *q);

// dequeue_print(q) prints the contents of q
// effects: prints to output
void dequeue_print(const struct dequeue *q);


double *deq_to_array(const struct dequeue *q);
