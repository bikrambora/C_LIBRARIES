/***********************************************************
 *          author BIKRAM KAUSHIK BORA                     *
 *                                                         *
 *    LinkedIn:   https://au.linkedin.com/in/bikrambora    *
 *                                                         *
 *    GitHub:     https://github.com/bikrambora            *
 ***********************************************************/
 
 /*
 ** This file contains the function prototypes and struct definitions used by the file heap.c
 **
 */


typedef struct item 
{
	int key; 					// the key for deciding position in heap
	unsigned int dataIndex; 	// the payload index provided by the calling program
}HeapItem;

typedef struct heap 
{
	HeapItem *H; 			// the underlying array
	unsigned int *map; 		// map[i] is index into H of location of payload with dataIndex == i
	unsigned int n; 		// the number of items currently in the heap
	unsigned int size; 		// the maximum number of items allowed in the heap
}Heap;



Heap *createHeap(int heapSize); 								//that returns a pointer to a new, empty heap
int insertMinHeap(Heap *h, unsigned int dataIndex, int key); 	//inserts dataIndex into h. Returns HEAP SUCCESS if it has inserted, or HEAP FAIL otherwise. used for Min Heaps Only.
int insertMaxHeap(Heap *h, unsigned int dataIndex, int key); 	//inserts dataIndex into h. Returns HEAP SUCCESS if it has inserted, or HEAP FAIL otherwise. used for Max Heaps Only.
unsigned int peek(Heap *h); 								    //returns the data index of the root.
int peekKey(Heap *h); 									        //returns the key of the root.

unsigned int removeMin(Heap *h);							    //removes the root, returns the data index to it, and re-heapifies (possibly changing other items map values). used for Min Heaps Only.
unsigned int removeMax(Heap *h);							    //removes the root, returns the data index to it, and re-heapifies (possibly changing other items map values). used for Max Heaps Only.

void changeKeyMin(Heap *h, unsigned int dataIndex, int delta);  //adds delta to the key of dataIndex and then re-heapifies. used for Min Heaps Only.
void changeKeyMax(Heap *h, unsigned int dataIndex, int delta);  //adds delta to the key of dataIndex and then re-heapifies. used for Max Heaps Only.


void destroyHeap(Heap *h); 									    //free any memory you might have malloced in heap creation.
