
#include <stdio.h>
#include "prioqueue.h"

#define LEFT(x) (2 * (x) + 1)
#define RIGHT(x) (2 * (x) + 2)
#define PARENT(x) ((x - 1 + (x%2)) / 2) // e.x. 7 <-- <3> --> 8,  7/2 --> 3, but 8/2 --> 4

/**
 *  swap two elements in a generic array 
 * @param array
 * @param i1
 * @param i2
 */

/*
 * 	create new prio queue
 * */
PrioQueue new_PrioQueue(int capacity){
    PrioQueue p = (PrioQueue)malloc(sizeof(struct prioQueue));
    p->array = (void**)malloc(sizeof(void*)*capacity);
    p->capacity = capacity;
    p->size = 0;
}

/*
 * 	adds element to the array, enlarges thge array if needed.
 * */
void add(PrioQueue queue,void * elem){
    if(queue->size == queue->capacity ){
        enlarge(queue);
	}
    queue->array[queue->size] = elem;
	shiftUp(queue,queue->size);
    queue->size ++;
	
}

/*
  
 *   ==o - - - %
 * doubles the size of an void ** array (generic array).
 */
void enlarge(PrioQueue queue){
    int i = 0;
    queue->capacity = queue->capacity*2;
    void ** new_array = (void**)malloc(sizeof(void*)*queue->capacity );
    for(i; i < queue->size;i++){
        new_array[i] = (void*)queue->array[i];
    }
    // free array pointed to by double pointer
    //queue->freeArray(queue->array,queue->size);
	free(queue->array);
    queue->array = new_array;
}

/*
 *	swap to elements in generic array 
 */
void swap(void ** array, int i1, int i2){
    void * temp = array[i1];
    array[i1] = array[i2];
    array [i2] = temp;
}

/*
 * 	shifts an element down the prio queue
 * */
void shiftDown(PrioQueue pq,int index){
    int ok = 0;
	int next;
    while(ok == 0 && index < pq->size){
        // compare left and right for largest element
		if(LEFT(index) < pq->size && RIGHT(index) < pq->size){
			if(pq->compare(pq->array[LEFT(index)],pq->array[RIGHT(index)]) >= 0){
					next = LEFT(index);
				}else{
					next = RIGHT(index);
					}
			if(pq->compare(pq->array[index],pq->array[next]) < 0){
					swap(pq->array,index, next);
					index = next;
				}else{
					ok = 1;
					}
		}
		// compare only left child to parent
        else if(LEFT(index) < pq->size && 
                pq->compare(pq->array[index],
                pq->array[LEFT(index)]) < 0 ){
            swap(pq->array,index, LEFT(index));
            index = LEFT(index);
        // compare only right child to parent
        }else if(RIGHT(index) < pq->size && 
                pq->compare(pq->array[index],
                pq->array[RIGHT(index)]) < 0){
            swap(pq->array,index, RIGHT(index));
            index = RIGHT(index);
        }else{
            ok = 1;
        }
    }
    
}

/*
 * 	shifts an element up the heap
 * */
void shiftUp(PrioQueue pq,int index){
		while(index > 0){
				if( pq->compare( pq->array[index], 
						pq->array[PARENT(index)]) > 0){
					swap(pq->array,index,PARENT(index));
					index = PARENT(index);
					}
				else{
						index = 0;
					}
			}
	}
	
/*
 * returns element with highest prority
 */
void * top_element(PrioQueue pq){
	if(pq->size>0){
		void * top = pq->array[0];
		if(pq->size>1){
			pq->array[0] = pq->array[pq->size-1];
			pq->size --;
			shiftDown(pq,0);
		}else{
			pq->size --;
			}
		return top;
		}
	return NULL;
	}
	
	void * peek_top(PrioQueue pq){
		if(pq->size > 0)
			return pq->array[0];
		return NULL;
		}
		
	
	// tail recursive function for checking heap property. 
	// returns 1 if a queue has heap property, else 0.
	int has_heap_property(PrioQueue pq, int index){
			if(index >= pq->size){
					return 1;
				}
			if(LEFT(index) < pq->size && pq->compare(pq->array[index],pq->array[LEFT(index)]) < 0){
					return 0;
				}
			if(RIGHT(index) < pq->size && pq->compare(pq->array[index],pq->array[RIGHT(index)]) < 0){
					return 0;
				}
			// returns 1 && 1 OR 0
			return has_heap_property(pq, LEFT(index)) * has_heap_property(pq, RIGHT(index));
				
		}