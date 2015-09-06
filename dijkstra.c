/***********************************************************
 *          author BIKRAM KAUSHIK BORA                     *
 *                                                         *
 *    LinkedIn:   https://au.linkedin.com/in/bikrambora    *
 *                                                         *
 *    GitHub:     https://github.com/bikrambora            *
 ***********************************************************/

/*
** This module implements dijkstra's shortest path algorithm
** It uses the graph heap and set modules
**
*/

//Based on Pseudocode from  Algorithms , S. Dasgupta, C. H. Papadimitriou, and U. V. Vazirani

#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <assert.h>
#include <stdio.h>

#include "heap.h"
#include "graph.h"
#include "set.h"

#define INITIAL_ARRAY_SIZE 10

//This functions explores the graph by using Dijkstra's algorithm and
//returns the set of homes accessible by it within the specified radius

void* dijkstra(Graph *g,unsigned int label,int max_dist,unsigned int numH,unsigned int numS)
{

	//create the heap that is to be used as a priority queue for getting min distances
	Heap *h = createHeap(numS+numH+1);
	assert(h);

	//initialize heap items with max integer value
	for(unsigned int i =0 ; i <(numS+numH) ; i++)
	{
			insertMinHeap(h, i, INT_MAX);
			
	}
	
	//Create a set to input the covered homes in
	Set* S=createSet(label);
	
	//initialize other variables used in the function
	unsigned int num_edges=0;
	int key=0;
	unsigned int label2=0;
	
	Edge *edges=NULL;
		
			
	int dist=0;
	
	
	//This Set holds the vertices already visited by dijkstra
	Set* R=createSet(0);

	
	assert(g);
	assert(h);
	
	h->n=numS+numH;
		
	//Initially change the key of the source node school to zero	
	changeKeyMin(h, label, (int)(key-((h->H[h->map[label]].key))));
	
	//Now traverse the graph according to the next nearest node as directed by the heap
	while((h->n>0)&&(max_dist>dist))
	{
		//set initial distance to distance of root
		dist=peekKey(h);
		
		//remove the minimum heap item i.e. nearest vertex
		label2=removeMin(h);
		
		edges = graph_get_edge_array(g,label2,&num_edges);
		
		
		//If vertex is not a school insert into the covered schools set
		if(!(numH<=label2)&&(label2<numH+numS))
		{
			insertInSet(S,label2);
		}
		//insert the vertex into the visited set
		insertInSet(R,label2);

		
		//for each edge of the current vertex update the keys in the heap
		//only if that vertex has not been visited yet
		for(unsigned int i=0;i<num_edges;i++)
		{
			//increase total distance covered
			key=(*(int*)edges[i].data)+dist;
			
			if(key<(h->H[h->map[edges[i].u]].key))
			{
				//update key only if vertex has not been visited yet
				if(presentInSet(R,edges[i].u)==0)
				{
					changeKeyMin(h, edges[i].u,(key-((h->H[h->map[edges[i].u]].key))));
				}
				
			}
		}
		//termination
		if(peekKey(h)>max_dist)
		{
			break;
		}
	}
	freeSet(R);
	//free the memory of the heap
	destroyHeap(h);

	return (void *)S;
}