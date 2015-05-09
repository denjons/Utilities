/* 
 * File:   main.c
 * Author: dennisj
 *
 * Created on December 15, 2014, 12:20 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "prioqueue.h"
#include "bst.h"

/*
 * 
 */

int bst_comapre_impl(void* k1,void* k2){
		char ck1 = *(char*)k1;
		char ck2 = *(char*)k2;
		if(ck1 < ck2){
				return -1;
			}
		else if (ck1 > ck2){
				return 1;
			}
		return 0;
	}
	
int free_bst(Bst bst){
		int i = 0;
		BstNode nodes[bst->size];
		int s = bst_toArray(bst,nodes);
		for(i;i<s;i++){
			free((char*)nodes[i]->key);
			free(nodes[i]);
			}
		free(bst);
	}
	

int main_compare(void* elem1, void * elem2){
    int elem11 = *((int*)elem1);
    int elem22 = *((int*)elem2);
    if(elem11 < elem22){
        return -1;
    }else if(elem11 > elem22){
        return 1;
    }
    return 0;
}

void free_array(void**array,int size){
    int i = 0;
    int * elem;
    for(i; i < size; i++){
        elem = (int*)array[i];
        free(elem);
    }
    free(array);
}


int main(int argc, char** argv) {
	
	printf("\n------------------- PRIO QUEUE TEST ------------------\n");
    // ------------------- PRIO QUEUE TEST ------------------
    PrioQueue pq = new_PrioQueue(2);
    //pq->freeArray = &free_array; // address of the function
    pq->compare = &main_compare;
	
	// add 100 elements
	int k=0;
	for(k;k<100;k++){
			int * i1 = (int*)malloc(sizeof(int));
			*i1 = k;
			add(pq,(void*)i1);
		}
	
	
	if(has_heap_property(pq,0) >= 1){
			printf("has heap property! xD\n");
		}
		else{
			printf("Does not have heap property! )`x\n");
			}

/*
    int i = 0;
    printf("size of array: %i \n",sizeof(pq->array));
    for(i;i<pq->size;i++){
        printf(" :) %i\n",*((int*)pq->array[i]));
    }
	 */
	
	// big sorted test
	
	PrioQueue pq2 = new_PrioQueue(2);
	//pq2->freeArray = &free_array; // address of the function
    pq2->compare = &main_compare;
	
	// test taking elements out of the queue!
	printf("sorted test! : \n");
	int * elem;
	while(pq->size > 0){
			elem = (int*)top_element(pq);
			// keep track of them with another queue.. 
			add(pq2,(void*)elem);
			printf(" x) size: %i, elem: %i\n",pq->size,*elem);
		}
	
    // pq2 should also have the heap property
	if(has_heap_property(pq2,0) >= 1){
			printf("pq2 has heap property! xD\n");
		}
		else{
			printf("pq2 Does not have heap property! )`x\n");
			}
    
    // free all memory
    free_array(pq->array,pq->size);
    free(pq);
	
	free_array(pq2->array,pq2->size);
    free(pq2);
	
	
	// ------------------- BST TEST ------------------
	printf("\n------------------- BST TEST ------------------\n");
	
	Bst bst = new_Bst();
	bst->compare = &bst_comapre_impl;
	int bi  = 0;
	char * c;
	int vals[]={6,5,3,4,9,8,10,2,1,13,20,11,7,15};
	char*chars[14];
	for(bi; bi < 14; bi ++){
			c = (char*)malloc(sizeof(char)); 
			*c = (65 + vals[bi]);
			chars[bi] = c;
			bst_insert(bst,c,bi);
		}
		
	BstNode b = bst->nodes; 
	
	printf("going left! oX \n");
	while(b != NULL){
			//printf(" x) key: %c, value %i\n",*((char*)b->key),b->value);
			b = b->left;
		}
		
	printf("\n ----------- getting all values ------------ \n");
	
	bi = 0;	
	BstNode res;
	for(bi;bi<14;bi++){
			res = bst_get(bst,chars[bi]);
			if(res != NULL){
				//printf(" x) key: %c, value %i\n",*chars[bi],res->value);
			}else{
				printf("res is of %c cannot be found! Dx\n",*chars[bi]);
			}
		}
		
		printf("\n --------- bst to array ---------- \n");
		
	BstNode nodesArray[bst->size];
	int s = bst_toArray(bst,nodesArray);
	bi = 0;
	for(bi;bi<s;bi++){
		//printf(" x) key: %c, value %i\n",*((char*)nodesArray[bi]->key),nodesArray[bi]->value);
		}
	
	free_bst(bst);
    return (EXIT_SUCCESS);
     
}

