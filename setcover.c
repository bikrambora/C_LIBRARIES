/***********************************************************
 *          author BIKRAM KAUSHIK BORA                     *
 *                                                         *
 *    LinkedIn:   https://au.linkedin.com/in/bikrambora    *
 *                                                         *
 *    GitHub:     https://github.com/bikrambora            *
 ***********************************************************/
 /*
 ** This module implements the set cover greedy algorithm
 ** as discussed in lectures
 ** it uses the set and the heap modules
 **
 */


#include "heap.h"
#include "set.h"
#include <assert.h>
#include <malloc.h>
#include <limits.h>
#include <stdio.h>

//This function prints out the sets that are required to span all of the homes
//using the sets provided by Dijkstra's algorithm

void setCover(Set **SetMap,Set* HeapSet,Heap* h,unsigned int numH)
{
	//Stores all the vertices already covered
	Set * AllSet=createSet(INT_MAX);
	
	//Stores the elements of the set which has the maximum number of uncovered items
	Set * NowSet=NULL;
	
	//Loop which removes from heap until either the heap is empty or all the houses have been covered
	while(AllSet->n<numH && h->n>0 && HeapSet->n>0)
	{
		//Set the root element of max heap as current set
		NowSet=SetMap[removeMax(h)];
		printf("%u\n",NowSet->name-numH);
		removeFromSet(HeapSet,NowSet->name);
		
		//Unite the schools of the removed 'largest uncovered' set with the ones already visited
		AllSet=unionSet(AllSet,NowSet);
		AllSet->name=INT_MAX;
		if(AllSet->n>=numH)
		{
			//break if all schools are spanned
			break;
		}
		
		//Remove the elements present in the 'largest uncovered set' from the sets still present in the heap
		if(HeapSet->n>0)
		{
			SetItem *curr=HeapSet->head;
			
			while(curr)
			{
				//Remove elements of Current set from all unviewed sets in the heap
				minusSet(SetMap[curr->Label],NowSet);
				//Update the keys
				changeKeyMax(h,SetMap[curr->Label]->name,(int)(SetMap[curr->Label]->n)-(h->H[h->map[curr->Label]].key));
				
				if(curr->next==NULL)
				{
					break;
				}
				else
				{
					curr=curr->next;
				}
				
			}
		}
		
		
	}
}