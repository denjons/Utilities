
struct linkedList{
		void*val;
		struct linkedList next;
		int (*compare)(void*,void*)
	}
	
typedef struct linkedList * LinkedList;

void ll_insert(LinkedList,void*);
void * ll_contains(LinkedList,void*);
void ll_remove(LinkedList,void*);
void * ll_get(int);
void * ll_remove(int);