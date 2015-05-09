/* 
 * File:   prioqueue.h
 * Author: dennisj
 *
 * Created on December 15, 2014, 12:21 PM
 */

#ifndef PRIOQUEUE_H
#define	PRIOQUEUE_H

struct prioQueue{
    int size;
    int capacity;
    void ** array;
    int (*compare)(void*elem1,void*elem2);
    void(*freeArray)(void*,int);
};

typedef struct prioQueue * PrioQueue; 

// returns a new prioQueue
PrioQueue new_PrioQueue(int);
// add something to a given array
void add(PrioQueue,void*elem);
// shift elements up the heap, takes a generic array and a compare function
void shiftUp(PrioQueue,int);
// shift elements down the heap, takes a generic array and a compare function 
void shiftDown(PrioQueue,int);
// takes a generic array and and removes an element from it 
void * top_element(PrioQueue);
// peek at top element
void * peek_top(PrioQueue);

int has_heap_property(PrioQueue,int);


#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* PRIOQUEUE_H */

