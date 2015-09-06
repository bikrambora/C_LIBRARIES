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


#include "set.h"
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

//This function allocates space for a set and initializes the variables
Set* createSet(unsigned int name)
{
	Set *S= (Set*)malloc(sizeof(*S));
	assert(S);
	
	//initialize the variables
	S->head  =NULL;
	S->name=name;
	S->n=0;
	S->foot = NULL;
	
	
	return S;
}



//Inserts an element into a Set if it is not present in it
//returns 1 if inserted 0 if not inserted
int insertInSet(Set *S, unsigned int Label) 
{
	assert(S);
	SetItem * newItem;
	newItem = (SetItem*)malloc(sizeof(SetItem));
	assert(newItem);
	newItem->Label = Label;
	newItem->next = NULL;
	newItem->prev = NULL;
	
	
	//Depending on the multiple cases the pointer manipulation varies
	
	//If no other elements exist
	if(S->n==0)
	{
		S->head=newItem;
		//S->foot=newItem;
		S->n++;
		return 1;
	}
	
	//If 1 other element exists
	if(S->n==1)
	{
		if(S->head->Label==Label)
		{
			free(newItem);
			return 1;
		}
		if(Label<S->head->Label)
		{
			newItem->next=S->head;
			S->head=newItem;
			S->n++;
			return 1;
		}
		if(Label>S->head->Label)
		{
			S->head->next=newItem;
			S->n++;
			return 1;
		}
	}
	
	//If more than 1 elements exist
	if(S->n>1)
	{
		//Incoming element is compared with first and second element of set
		//Sets are always kept in sorted order
		if(Label<S->head->Label)
		{
			newItem->next=S->head;
			S->head=newItem;
			S->n++;
			return 1;
		}
		if(Label<S->head->next->Label)
		{
			newItem->next=S->head->next;
			S->head->next=newItem;
			S->n++;
			return 1;
		}
		SetItem *curr=S->head;
		
		//Check to see if element is already present
		while(curr->next)
		{
			if(Label==curr->Label||Label==curr->next->Label)
			{
				free(newItem);
				return 0;
			}
			
			//If not present then insert element in Set.
			if((curr->Label<Label)&&(Label<curr->next->Label))
			{
				newItem->next=curr->next;
				curr->next=newItem;
				S->n++;
				return 1;
			}
			
			if(curr->next==NULL)
			{
				break;
			}
			else
			{
				curr=curr->next;
			}
		}
		
		curr->next=newItem;
		S->n++;
		return 1;		
	}
	return 0;
}

//Remove specific element from Set
//Returns 1 if removed other wise returns 0
int removeFromSet(Set *S, unsigned int Label) 
{
	//Depending on the multiple cases the pointer manipulation varies
	
	//If no elements exist
	if(S->n==0)
	{
		return 0;
	}
	//If number of elements is more than zero
	if(S->n>0)
	{
		//check if element is at head
		if(Label==S->head->Label)
		{
			SetItem *temp=S->head;
			S->head=S->head->next;
			free(temp);
			S->n--;
			return 1;
		}
		
		//if there are more than 1 elements in the set
		if(S->n>1)
		{	
			//if second element is to be removed
			if(Label==S->head->next->Label)
			{
				SetItem *temp=S->head->next;
				S->head->next=S->head->next->next;
				free(temp);
				S->n--;
				return 1;
			}
			
			SetItem *curr=S->head;
			
			//traverse linked list and search for element
			while(curr->next)
			{
				//when found manipulate the pointers appropriately 
				//and free the memory occupied by that node
				if(Label==curr->next->Label)
				{
					SetItem *temp=curr->next;
					if(curr->next->next)
					{
						curr->next=curr->next->next;
					}
					else
					{
						curr->next=NULL;
					}
					
					free(temp);
					S->n--;
					return 0;
				}
				//Loop termination
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
	return 0;
}
	
//Checks if an element is present in a set 
//and returns 1 if it is otherwise returns 0
int presentInSet(Set *S, unsigned int Label)
{
	assert(S);
	if(S->n>0)
	{
		SetItem *curr=S->head;
		//Traverse and check equality
		while(curr)
		{
			if(curr->Label==Label)
			{
				return 1;
			}
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
	return 0;
} 

//Prints the elements of the set on a single line separated by 
//a space along with its name and size
void printSet(Set *S)
{
	assert(S);
	printf("\n****PRINTING***SET : %u\n",S->name);
	printf("Size: %u\n",S->n);
	if(S->n>0)
	{
		SetItem *curr=S->head;
		
		//Traverse and print
		while(curr)
		{
			printf("%u ",curr->Label);
			
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
	printf("\n****over*****\n");
}

//Unions Set S1 and S2 and returns a pointer to the united set
//This union is done based on the sizes
//Smaller in pushed into the larger
Set* unionSet(Set* S1, Set* S2)
{
	Set* Sbig=NULL;
	Set* Ssmall=NULL;
	
	//take care of some special cases if anyset has 0 elements
	if(S1->n==0 && S2->n!=0)
	{
		return S2;
	}
	if(S1->n!=0 && S2->n==0)
	{
		return S1;
	}
		
	if(S1->n==0 && S2->n==0)
	{
		return S1;
	}
	
	//decide which set is bigger
	if(S1->n<S2->n)
	{
		Sbig=S2;
		Ssmall=S1;
	}
	else
	{
		Sbig=S1;
		Ssmall=S2;
	}
	SetItem * curr= Ssmall->head;
	
	//Insert elements of smaller set into the bigger
	while(curr)
	{
		insertInSet(Sbig,curr->Label);
		
		if(curr->next==NULL)
		{
			break;
		}
		else
		{
			curr=curr->next;
		}
	}
	return Sbig;
		
}

//Remove elements present in set S2 from set S1
void minusSet(Set* S1, Set* S2)
{
	if(S1->n==0|| S2->n==0)
	{
		return;
	}
	SetItem * curr= S2->head;
	
	//Traverse set S2 and remove its elements from S1
	while(curr)
	{
		removeFromSet(S1,curr->Label);
		
		if(curr->next==NULL)
		{
			break;
		}
		else
		{
			curr=curr->next;
		}
	}
	return;
	
}
//Returns 1 if set is empty otherwise returns 0
int isEmptySet(Set *S) 
{
	assert(S);
	return S->head==NULL;
}

//free the memory allocated to the set
void freeSet(Set *S) 
{
	SetItem *curr, *prev;
	assert(S!=NULL);
	curr = S->head;
	
	//Traverse each element and free the node
	while (curr) 
	{
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(S);
}