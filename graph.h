/***********************************************************
 *          author BIKRAM KAUSHIK BORA                     *
 *                                                         *
 *    LinkedIn:   https://au.linkedin.com/in/bikrambora    *
 *                                                         *
 *    GitHub:     https://github.com/bikrambora            *
 ***********************************************************/

 /*
 ** This file contains the function prototypes and struct definitions 
 ** for the functions and structs used in graph.c
 **
 */
 

/*
** Graph data type
** Uses an adjacency list representation (arrays for lists).
** Written for workshop 3 of COMP20007
**
** Andrew Turpin
** Tue 17 Mar 2015 19:13:47 AEDT
*/


/*Functions graph_connectivity_check and graph_explore have been added by Bikram Kaushik Bora
**
*/
typedef unsigned int Label;   // a vertex label (should be numeric to index edge lists)

typedef struct {
    void   *data;   // any data you want to store about an edge
    Label u;        // end vertex of edge
} Edge;

typedef struct {
    void   *data;        // any data to store about a vertex
    Label  label;        // this vertex's label
    Edge  *edges;        // array of edges [0..num_edges-1]
    unsigned int   num_edges;     // number of edges
    unsigned int   max_num_edges; // current malloced size of edges array, num_edges <= max_num_edges
} Vertex;

typedef struct {
    void   *data;              // any data you want to store about a graph
    unsigned int    number_of_vertices; // |V|
    Vertex *vertices;          // array of vertices [0..number_of_vertices-1]
} Graph;

// prototypes

Graph *graph_new(int number_of_vertices);   //allocates space for a new graph
void  graph_add_edge(Graph *g, Label v, Label u, void *data);  //adds edge from v to u
void  graph_del_edge(Graph *g, Label v, Label u);   //deletes edge which goes from vertex v to u
int   graph_has_edge(Graph *g, Label v, Label u);   //checks if there is an edge from v to u
Edge *graph_get_edge_array(Graph *g, Label v, unsigned int *num_edges); //Returns a pointer to the beginning of the edge array

void  graph_set_vertex_data(Graph *g, Label v, void *data); //sets the vertex's data to the argument data

void graph_connectivity_check(Graph *g, Label v,unsigned int * count, void (explore)(Graph *g, Label v,unsigned int * count));  //checks if graph is completely connected
void graph_explore(Graph *g, Label v, unsigned int * count); //recursive DFS explore

void graph_default_explore(Graph *g, Label v);  //default recursive explore present in skeleton
void graph_dfs(Graph *g, Label v, void (explore)(Graph *g, Label v));  //calls DFS explore on a target vertex

void freeGraph(Graph *g); //frees all the memory malloced for the graph


