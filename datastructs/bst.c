
#include <stdio.h>
#include "bst.h"

/*
 * 	create new bst node
 * */
BstNode new_BstNode(void* key, long value){
		BstNode bst = (BstNode)malloc(sizeof(struct bst_node));
		bst->key = key;
		bst->value = value;
		bst->left = NULL;
		bst->right = NULL;
		return bst;
	}
	
/*
 * 	create new bin search tree
 * */
Bst new_Bst(){
		Bst bst = (Bst)malloc(sizeof(struct binSearchTree));
		bst->size = 0;
		bst->nodes = NULL;
		bst->compare = NULL;
		return bst;
	}
	
/*
 * insert
 * */
int bst_insert(Bst bst, void* key, long value){
	
		BstNode next;
		BstNode before;
		BstNode ins_node = new_BstNode(key,value);
		bst->size ++;
		
		if(bst->nodes == NULL){
			bst->nodes = ins_node;
			return 1;
			}
			
		next = bst->nodes;
		while( next != NULL ){
				if(bst->compare(ins_node->key,next->key) > 0){
						before = next;
						next = next->right;
						if(next == NULL)
							before->right = ins_node;
					}
				else if(bst->compare(ins_node->key,next->key) < 0){
						
						before = next;
						next = next->left;
						if(next == NULL)
							before->left = ins_node;
				}
			}
			return 1;
	}
	
	BstNode bst_get(Bst bst,void*key){
			BstNode next = bst->nodes;
			while(next != NULL){
				// debug
				//printf("passing %c: (%c, %i), ",*((char*)key),*((char*)next->key),next->value);
				if(bst->compare(key,next->key) == 0){
						return next;
					}
				else if(bst->compare(key,next->key) > 0){
						next = next->right;
					}
				else{
					next = next->left;
					}
				}
				printf("done\n");
				return NULL;
		}
		
		int bst_toArray(Bst bst, BstNode * array){
				return bst_NodeArray(bst->nodes,array,0);
			}
			
		 int bst_NodeArray(BstNode bstNode, BstNode * array ,int size){
				if(bstNode == NULL)
					return size;
				array[size] = bstNode;
				//printf("size of array %i : (%c,%i)\n",size,*((char*)array[size]->key),array[size]->value);
				size ++;
				size = bst_NodeArray(bstNode->left,array,size);
				return bst_NodeArray(bstNode->right,array,size);
			}
		 


	
