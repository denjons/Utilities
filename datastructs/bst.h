#ifndef BST_H
#define	BST_H
	
struct bst_node{
		unsigned long value;
		void * key;
		struct bst_node * left;
		struct bst_node * right;
	};
	
typedef struct bst_node * BstNode;

struct binSearchTree{
		int size;
		// (double pointer)
		BstNode nodes;
		int (*compare)(void*,void*);
	};
	
typedef struct binSearchTree * Bst;

// new bst
Bst new_Bst();
// new bst node
BstNode new_BstNode(void*, long);
// insert element into a binary search tree
int bst_insert(Bst,void*, long);
// find a value with a given key
BstNode bst_get(Bst,void*);
// removes a bst node wih a given key
void * bst_remove(Bst,void*);
// get an array of all nodes
int bst_toArray(Bst,BstNode*); 
// collects all nodes from a bst node


#endif	

