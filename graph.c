/***********************************************************
 *          author BIKRAM KAUSHIK BORA                     *
 *                                                         *
 *    LinkedIn:   https://au.linkedin.com/in/bikrambora    *
 *                                                         *
 *    GitHub:     https://github.com/bikrambora            *
 ***********************************************************/
 /*
 ** This module contains functions for creating and querying Graphs
 ** The function prototypes and structs exist in graph.h
 */
 
 
/*
** Graph data type
** Uses an adjacency list representation (arrays for lists).
** Written for workshop 3 of COMP20007
** 
** Skeleton Code By
** Andrew Turpin
** Tue 17 Mar 2015 19:13:47 AEDT
** Added to by Champak Mendis
** 
**
*/

/*
**  Modified For Assignment2 By Bikram Kaushik Bora
**
*/


#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

/*
** Allocates memory for a new graph structure
** Initializes variables
** Mallocs the Various Components
*/
Graph* graph_new(int number_of_vertices) 
{
	//check input arguments and malloc space for the graph
    assert(number_of_vertices > 0);
    Graph *g = (Graph *)malloc(sizeof(Graph));
    assert(g);
	
    g->data = NULL;
    g->number_of_vertices = number_of_vertices;
    g->vertices = (Vertex *)malloc(sizeof(Vertex) * number_of_vertices);
    assert(g->vertices);
	
	//loop to initialize the variables
    for(int i = 0 ; i < number_of_vertices ; i++) 
	{
        g->vertices[i].data  = NULL;
        g->vertices[i].label = i;
        g->vertices[i].edges = NULL;
        g->vertices[i].num_edges = 0;
        g->vertices[i].max_num_edges = 0;
    }
    
	//return newly created graph pointer
    return(g);
}

/*
** This function adds an edge between two graph vertices 
** The vertices come in as input arguments
** Edge is added in the vertex array of only the first argument vertex
*/
void graph_add_edge(Graph *g, Label v, Label u, void *data) 
{
    assert(g);
	assert(data);
    assert(v >= 0 && v < g->number_of_vertices);
    assert(u >= 0 && u < g->number_of_vertices);

    //If there is no room double the size of the array by reallocing.
    if (g->vertices[v].num_edges == g->vertices[v].max_num_edges) 
	{
        if (g->vertices[v].max_num_edges == 0)
		{
            g->vertices[v].max_num_edges = 1;
		}
        else
		{
            g->vertices[v].max_num_edges *= 2;
		}
		//doubling size of array
        g->vertices[v].edges = (Edge *)realloc(g->vertices[v].edges, sizeof(Edge)*g->vertices[v].max_num_edges);
        assert(g->vertices[v].edges);
    }

    g->vertices[v].edges[g->vertices[v].num_edges].u    = u;
    g->vertices[v].edges[g->vertices[v].num_edges].data = data;
	
	//increase number of edges counter
    g->vertices[v].num_edges += 1;
}

/*
** This function deletes an edge between two vertices
** The edge is deleted only from the edge array of the first argument vertex
*/
void graph_del_edge(Graph *g, Label v, Label u) 
{
	//check input arguments
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);
    assert(u >= 0 && u < g->number_of_vertices);

    unsigned int i;

    for(i = 0 ; i < g->vertices[v].num_edges && g->vertices[v].edges[i].u != u ; i++);
        
    if (i == g->vertices[v].num_edges) // not there
	{
        return;
	}
	
	//if edge exists ten it is removed
    for( ; i < g->vertices[v].num_edges - 1 ; i++) // move remaining edges to the left to fill the hole at i
	{
        g->vertices[v].edges[i] = g->vertices[v].edges[i+1];
	}
	
	//decrease number of edges
    g->vertices[v].num_edges -= 1;
}

/*
** This function returns a pointer that points to the start of edge array for vertex v
** Set pointer num_edges to the number of items in the edge array.
*/
Edge* graph_get_edge_array(Graph *g, Label v, unsigned int *num_edges) 
{
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);

	//assign the number of edges as value of the pointer
    *num_edges = g->vertices[v].num_edges;
	
	//return pointer that points to the start of the edge array
    return g->vertices[v].edges;
}

/*
** This function returns 1 if an edge exists from v to u and otherwise 0
** 
*/
int graph_has_edge(Graph *g, Label v, Label u) 
{
	//check input arguments
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);
    assert(u >= 0 && u < g->number_of_vertices);
    
    for(unsigned int i = 0 ; i < g->vertices[v].num_edges ; i++)
	{
		//check all edges and return 1 if edge exists
        if (g->vertices[v].edges[i].u == u)
		{
            return 1;
		}
	}

    return 0;
}


/*
** This function sets the vertex's data to the value of the input argument data
*/
void graph_set_vertex_data(Graph *g, Label v, void *data) 
{
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);
    
    g->vertices[v].data = data;
}

/*
** This function does a depth first explore starting at the input vertex
** It adds 1 to the pointer argument count each time it encounters a new vertex
** At the main function this count variable is used to check if the graph is completely connected
** ASSUMES vertex->data is 1 or 0 for visited and unvisted
*/
void graph_explore(Graph *g, Label v, unsigned int * count) 
{
	//if vertex has already been visited we do not increase the counter and do not call explore on it again
    if (g->vertices[v].data)
	{
        return;
	}

	// mark as visited
    g->vertices[v].data = (void *)1; 
	
	//increment counter
	*count=*count+1; 

	//call DFS on this vertex
    for(unsigned int i = 0 ; i < g->vertices[v].num_edges ; i++)
	{
        graph_explore(g, g->vertices[v].edges[i].u,count);
	}
}

/*This function start the DFS explore on the graph and accepts a 
**pointer that acts a a counter variable to keep track of the number of vertices visited
*/

void graph_connectivity_check(Graph *g, Label v, unsigned int * count,void (explore)(Graph *g, Label v, unsigned int * count)) 
{
	//check inputs
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);

    // call the first explore first explore from v
	//this starts the DFS recursive explore
    explore(g, v,count);
}


/*
** This function was availble pre-written in the skeleton and 
** is not used in the assignment but simply kept to add more functionality to the module
**
** Simple explore for calling from dfs that doesn't actually do anything.
** Use as a template for writing your own explore() functions.
** ASSUMES vertex->data is 1 or 0 for visited and unvisted 
**
*/
void 
graph_default_explore(Graph *g, Label v) {
    if (g->vertices[v].data)
        return;

    g->vertices[v].data = (void *)1; // mark as visited

    for(unsigned int i = 0 ; i < g->vertices[v].num_edges ; i++)
        graph_default_explore(g, g->vertices[v].edges[i].u);
}

/*
** This function was available pre-written in the skeleton and 
** is not used in the assignment but simply kept to add more functionality to the module
**
** Perform DFS beginning at v, calling pre() and post() as appropriate.
** ASSUMES vertex->data is 1 or 0 for visited and unvisted 
** pre and post can be NULL
**
*/
void 
graph_dfs(Graph *g, Label v, void (explore)(Graph *g, Label v)) {
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);

    // first explore from v
    explore(g, v);


    // now do the rest (if any)
    for(unsigned int i = 0; i < g->number_of_vertices ; i++)
        explore(g, i);
}

//frees all the memory malloced for the graph
void freeGraph(Graph *g)
{
	free(g->data);
    free(g->vertices);
	free(g);
}
