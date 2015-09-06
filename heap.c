/***********************************************************
 *          author BIKRAM KAUSHIK BORA                     *
 *                                                         *
 *    LinkedIn:   https://au.linkedin.com/in/bikrambora    *
 *                                                         *
 *    GitHub:     https://github.com/bikrambora            *
 ***********************************************************/
 
 /*
** This module contains functions for creating and querying Heaps can be
** It can be used for both Min Heaps and Max Heaps but the appropriate functions must be used
** The function prototypes and structs exist in heap.h
*/
 

#include "heap.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define HEAP_FAIL 0
#define HEAP_SUCCESS 1


/* function prototype to internal functions */

void sift_up_Min  (Heap*,unsigned int,int,unsigned int);
void sift_down_Min(Heap*,unsigned int,int,unsigned int);

void sift_up_Max  (Heap*,unsigned int,int,unsigned int);
void sift_down_Max(Heap*,unsigned int,int,unsigned int);


// This function allocates space for a heap and initializes its variables

Heap *createHeap(int heapSize)//that returns a pointer to a new, empty heap
{
	
	//malloc heap
	Heap* h=(Heap*)malloc(sizeof(Heap));
	assert(h);
	
	h->size=heapSize;
	
	//malloc heap array
	HeapItem *H=(HeapItem*)malloc(sizeof(HeapItem)*heapSize);
	assert(H);
	
	h->H=H;
	h->n=0;
	
	//malloc the map array
	h->map=(unsigned int*)malloc(sizeof(unsigned int)*heapSize);
	
	assert(h->map);
	
	return h;
} 										

//This function inserts dataIndex into h. Returns HEAP_SUCCESS if it has inserted, or HEAP_FAIL otherwise.
//This to be used only for min heaps
int insertMinHeap(Heap *h, unsigned int dataIndex, int key) 
{
	//check if the dataIndex in within the heap size
	if(dataIndex>=h->size)
	{	
		return HEAP_FAIL;
	}
	//Heap is enlarged if required
	if(h->n==(h->size-1))
	{
		h->size*=2;
		realloc(h->H,sizeof(HeapItem)*h->size);
		assert(h->H);
	}
	
	//set the current end of the heap array to the new dataindex and key and then sift_up
	(h->H[h->n]).dataIndex=dataIndex;
	(h->H[h->n]).key=key;
	
	h->map[dataIndex]=h->n;
	
	h->n++;
	
	//sift_up
	if(h->n>=1)
	{
		sift_up_Min(h,dataIndex,key,h->n-1);
	}
	return HEAP_SUCCESS;
}	

//This function inserts dataIndex into h. Returns HEAP_SUCCESS if it has inserted, or HEAP_FAIL otherwise.
//This to be used only for max heaps
int insertMaxHeap(Heap *h, unsigned int dataIndex, int key) //inserts dataIndex into h. Returns HEAP SUCCESS if it has inserted, or HEAP FAIL otherwise.
{
	//check if the dataIndex in within the heap size
	if(dataIndex>=h->size)
	{	
		return HEAP_FAIL;
	}
	//Heap is enlarged if required
	if(h->n==(h->size-1))
	{
		h->size*=2;
		realloc(h->H,sizeof(HeapItem)*h->size);
		assert(h->H);
	}
	
	
	(h->H[h->n]).dataIndex=dataIndex;
	(h->H[h->n]).key=key;
	h->map[dataIndex]=h->n;
	
	h->n++;
	
	//set the current end of the heap array to the new dataindex and key and then sift_up	
	if(h->n>=1)
	{
		sift_up_Max(h,dataIndex,key,h->n-1);
	}
	return HEAP_SUCCESS;
}	

//returns the data index of the root.
unsigned int peek(Heap *h) 
{
	return (h->H[0]).dataIndex;
}

//returns the key of the root.
int peekKey(Heap *h)    
{
	return (h->H[0]).key;
}

//removes the root, returns the data index to it, and re-heapifies (possibly changing other items map values).
//returns minimum value of heap in min heap, to be only used with min heaps
unsigned int removeMin(Heap *h)
{	
	if(h->n<=0)
	{
		return INT_MAX;
	}
	
	unsigned int data_index=(h->H[0]).dataIndex;
	
	h->H[0]=h->H[h->n-1]; //Remove root

	h->map[h->H[0].dataIndex]=0; //put the last value int the root and then reheapify

	h->n--;

	if(h->n>0)
	{
		sift_down_Min(h,h->H[0].dataIndex,h->H[0].key,h->map[h->H[0].dataIndex]);
	}
	
	return data_index;
}


//removes the root, returns the data index to it, and re-heapifies (possibly changing other items map values).
//returns minimum value of heap in max heap, to be only used with max heaps
unsigned int removeMax(Heap *h)
{
	if(h->n==0)
	{
		return 0;
	}
	
	unsigned int data_index=(h->H[0]).dataIndex;
	
	h->H[0]=h->H[h->n-1]; //Remove root

	h->map[h->H[0].dataIndex]=0; //put the last value int the root and then reheapify

	h->n--;

	if(h->n>0)
	{
		sift_down_Max(h,h->H[0].dataIndex,h->H[0].key,h->map[h->H[0].dataIndex]);
	}
	
	return data_index;
}

//adds delta to the key of dataIndex and then re-heapifies.
//To be only used with Min Heap
void changeKeyMin(Heap *h, unsigned int dataIndex, int delta)
{
	//add delta to the key of the heap item
	(h->H[h->map[dataIndex]]).key+=delta;

	//depending on the value of delta call sift_up or sift_down
	if(delta>0)
	{
		//call sift_down_min
		sift_down_Min(h,dataIndex,(h->H[h->map[dataIndex]]).key,h->map[dataIndex]);
	}
	if(delta<0)
	{
		//call sift_up_min
		sift_up_Min  (h,dataIndex,(h->H[h->map[dataIndex]]).key,h->map[dataIndex]);
	}
		
	return;
}

//adds delta to the key of dataIndex and then re-heapifies.
//To be only used with Max Heap
void changeKeyMax(Heap *h, unsigned int dataIndex, int delta)//adds delta to the key of dataIndex and then re-heapifies.
{
	//depending on the value of delta call sift_up or sift_down
	(h->H[h->map[dataIndex]]).key+=delta;

	//depending on the value of delta call sift_up or sift_down
	if(delta<0)
	{
		//call sift down
		sift_down_Max(h,dataIndex,(h->H[h->map[dataIndex]]).key,h->map[dataIndex]);
	}
	if(delta>0)
	{
		//sift_up_Min(h,dataIndex,key,h->n-1);
		sift_up_Max  (h,dataIndex,(h->H[h->map[dataIndex]]).key,h->map[dataIndex]);
	}

	
	return;
}

//free any memory you might have malloc'd in heap creation.
void destroyHeap(Heap *h)
{
	free(h->map);
	free(h->H);
	free(h);
	return;
}


//sifts up according to key comparisons
//only to be used with Min Heap
void sift_up_Min(Heap *h,unsigned int dataindex,int key,unsigned int index)
{
	//base case of recursion
	//If index 0 then current element is at root so no parent
	if(index==0)
	{
		h->map[h->H[index].dataIndex]= index;
		return;
	}
	unsigned int temp_dataIndex;
	int temp_key;
	unsigned int parentIndex=0;
	
	//get the parents index
	parentIndex=(index-1)/2;
	
	//based on parent's key the decision is made
	if(h->H[index].key<h->H[parentIndex].key)
	{
		//exchange keys with parent and manipulate the map
		temp_dataIndex=h->H[index].dataIndex;
		temp_key=h->H[index].key;
		
		h->H[index].dataIndex               = h->H[parentIndex].dataIndex;
		h->H[index].key                     = h->H[parentIndex].key;
		h->map[h->H[parentIndex].dataIndex] = index;
		
		
		h->H[parentIndex].dataIndex       =temp_dataIndex;
		h->H[parentIndex].key             =temp_key;
		h->map[temp_dataIndex]            =parentIndex;
		
		//recursively call sift_up
		if(parentIndex>0)
		{
			sift_up_Min(h,dataindex,key,parentIndex);
		}
	}
	else
	{
		//otherwise simply manipulate the map
		h->map[h->H[index].dataIndex]= index;
		
	}
	return;
	
}


//sifts up according to key comparisons
//only to be used with Max Heap
void sift_up_Max(Heap *h,unsigned int dataindex,int key,unsigned int index)
{
	//base case of recursion
	//If index 0 then current element is at root so no parent
	if(index==0)
	{
		//printf("Inside index=0\n");
		h->map[h->H[index].dataIndex]= index;
		return;
	}
	unsigned int temp_dataIndex;
	int temp_key;
	unsigned int parentIndex=0;
	
	//get the parents index
	parentIndex=(index-1)/2;
	
	
	//based on parent's key the decision is made
	if(h->H[index].key>h->H[parentIndex].key)
	{
		//exchange keys with parent and manipulate the map
		temp_dataIndex=h->H[index].dataIndex;
		temp_key=h->H[index].key;
		
		h->H[index].dataIndex               = h->H[parentIndex].dataIndex;
		h->H[index].key                     = h->H[parentIndex].key;
		h->map[h->H[parentIndex].dataIndex] = index;
		
		
		h->H[parentIndex].dataIndex       =temp_dataIndex;
		h->H[parentIndex].key             =temp_key;
		h->map[temp_dataIndex]            =parentIndex;
		
		//recursively call sift_up
		if(parentIndex>0)
		{
			sift_up_Max(h,dataindex,key,parentIndex);
		}
	}
	else
	{
		//otherwise simply manipulate the map
		h->map[h->H[index].dataIndex]= index;
		
	}
	return;
	
}


//sifts down according to key comparisons
//only to be used with Min Heap
void sift_down_Min(Heap *h,unsigned int dataIndex,int key,unsigned int index)
{
	unsigned int temp_dataIndex1;
	int temp_key1;
	
	unsigned int temp_dataIndex2;
	int temp_key2;
	
	//get the children indices
	unsigned int childIndex1=(index*2)+1;
	unsigned int childIndex2=(index*2)+2;
	unsigned int smallerChildIndex=0;
	
	//used for flagging whether an exchange need to be done or no
	int flag=0;
	
	//depending on the multiple cases of the existence/non-existence of children
	//and the values of their keys the decision is made
	
	//if only 1 child present
	if(childIndex1<=h->n-1)
	{
		//If both children are present
		if(childIndex2<=h->n-1)
		{
			//compare keys of children
			if(h->H[childIndex1].key<h->H[childIndex2].key)
			{
				if(key>h->H[childIndex1].key)
				{
					smallerChildIndex=childIndex1;
					flag=1;
				}
				
			}
			else
			{
				if(key>h->H[childIndex2].key)
				{
					smallerChildIndex=childIndex2;
					flag=1;
				}
			}
		}
		else
		{
			if(key>h->H[childIndex1].key)
			{
					smallerChildIndex=childIndex1;
					flag=1;
			}
		}
		
		//using the flag as a marker for exchange
		if(flag==1)
		{
			//exchange the key and dataindex of child and parent
			temp_dataIndex1  = h->H[smallerChildIndex].dataIndex;
			temp_key1        = h->H[smallerChildIndex].key;
			
			temp_dataIndex2  = h->H[index].dataIndex;
			temp_key2        = h->H[index].key;
			
			//manipulate the map
			h->H[smallerChildIndex].dataIndex=temp_dataIndex2;
			h->H[smallerChildIndex].key=temp_key2;
			
			h->H[index].dataIndex=temp_dataIndex1;
			h->H[index].key=temp_key1 ;
			
			h->map[h->H[smallerChildIndex].dataIndex] = smallerChildIndex;
			h->map[h->H[index].dataIndex] = index;
			
			//recursively call sift_down			
			sift_down_Min(h,dataIndex,key,smallerChildIndex);
		}
		
	}
	
	return;	
}

//sifts down according to key comparisons
//only to be used with Max Heap
void sift_down_Max(Heap *h,unsigned int dataIndex,int key,unsigned int index)
{
	
	unsigned int temp_dataIndex1;
	int temp_key1;
	
	unsigned int temp_dataIndex2;
	int temp_key2;
	
	//get the children indices
	unsigned int childIndex1=(index*2)+1;
	unsigned int childIndex2=(index*2)+2;
	unsigned int biggerChildIndex=0;
	
	//used for flagging whether an exchange need to be done or not
	int flag=0;
	
	//depending on the multiple cases of the existence/non-existence of children
	//and the values of their keys the decision is made
	
	//if only 1 child present
	if(childIndex1<=h->n-1)
	{
		//If both children are present
		if(childIndex2<=h->n-1)
		{
			//compare keys of children
			if((h->H[childIndex1].key)>(h->H[childIndex2].key))
			{
				if(key<h->H[childIndex1].key)
				{
					biggerChildIndex=childIndex1;
					flag=1;
				}
				
			}
			else
			{
				
				if(key<(h->H[childIndex2].key))
				{
					
					biggerChildIndex=childIndex2;
					flag=1;
				}
			}
		}
		else
		{
			if(key<h->H[childIndex1].key)
			{
					biggerChildIndex=childIndex1;
					flag=1;
			}
		}
		
		//using the flag as a marker for exchange
		if(flag==1)
		{
			//exchange the key and dataindex of child and parent
			temp_dataIndex1  = h->H[biggerChildIndex].dataIndex;
			temp_key1        = h->H[biggerChildIndex].key;
			
			temp_dataIndex2  = h->H[index].dataIndex;
			temp_key2        = h->H[index].key;
			
			//manipulate the map
			h->H[biggerChildIndex].dataIndex=temp_dataIndex2;
			h->H[biggerChildIndex].key=temp_key2;
			
			h->H[index].dataIndex=temp_dataIndex1;
			h->H[index].key=temp_key1 ;
			
			h->map[h->H[biggerChildIndex].dataIndex] = biggerChildIndex;
			h->map[h->H[index].dataIndex] = index;
			
			//recursively call sift down			
			sift_down_Max(h,dataIndex,key,biggerChildIndex);
		}
		
	}
	
	return;	
}