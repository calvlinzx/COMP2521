    // Graph.c ... implementation of Graph ADT
// Written by John Shepherd, May 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "Queue.h"

#define MAXV 40

static void reversePath(int *a, int length);

// graph representation (adjacency matrix)
typedef struct GraphRep {
	int nV;		 // #vertices
	int nE;		 // #edges
	int **edges; // matrix of weights (0 == no edge)
} GraphRep;

// check validity of Vertex
int validV (Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}
/*
// make an edge
static Edge mkEdge (Graph g, Vertex v, Vertex w)
{
	assert (g != NULL && validV (g, v) && validV (g, w));
	Edge new = {v, w}; // struct assignment
	return new;
}
*/
// insert an Edge
// - sets (v,w) and (w,v)
void insertEdge (Graph g, Vertex v, Vertex w, int wt)
{
	assert (g != NULL && validV (g, v) && validV (g, w));

	if (g->edges[v][w] != 0 && g->edges[w][v] != 0)
		// an edge already exists; do nothing.
		return;

	g->edges[v][w] = wt;
	g->edges[w][v] = wt;
	g->nE++;
}

// remove an Edge
// - unsets (v,w) and (w,v)
void removeEdge (Graph g, Vertex v, Vertex w)
{
	assert (g != NULL && validV (g, v) && validV (g, w));
	if (g->edges[v][w] == 0 && g->edges[w][v] == 0)
		// an edge doesn't exist; do nothing.
		return;

	g->edges[v][w] = 0;
	g->edges[w][v] = 0;
	g->nE--;
}

// create an empty graph
Graph newGraph (int nV)
{
	assert (nV > 0);

	GraphRep *new = malloc (sizeof *new);
	assert (new != NULL);
	*new = (GraphRep){ .nV = nV, .nE = 0 };

	new->edges = calloc ((size_t) nV, sizeof (int *));
	assert (new->edges != NULL);
	for (int v = 0; v < nV; v++) {
		new->edges[v] = calloc ((size_t) nV, sizeof (int));
		assert (new->edges[v] != 0);
	}

	return new;
}

// free memory associated with graph
void dropGraph (Graph g)
{
	assert (g != NULL);
	for (int v = 0; v < g->nV; v++)
		free (g->edges[v]);
	free (g->edges);
	free (g);
}

// display graph, using names for vertices
void showGraph (Graph g, char **names)
{
	assert (g != NULL);
	printf ("#vertices=%d, #edges=%d\n\n", g->nV, g->nE);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		printf ("%d %s\n", v, names[v]);
		for (w = 0; w < g->nV; w++) {
			if (g->edges[v][w]) {
				printf ("\t%s (%d)\n", names[w], g->edges[v][w]);
			}
		}
		printf ("\n");
	}
}

// find a path between two vertices using breadth-first traversal
// only allow edges whose    is less than "max"
int findPath (Graph g, Vertex src, Vertex dest, int max, int *path)
{
	assert (g != NULL);

    int visited[MAXV];	
	int hop = 0;
	int i, found;
	
	if (src == dest) {
	    path[hop] = src;
	    hop++;
	}
	else if (g->edges[src][dest] < max) {
	    path[hop] = src;
	    hop++;
	    path[hop] = dest;
	    hop++;
	}
	else {
	    for (i = 0; i < g->nV; i++) {
	        visited[i] = -1; 
	    }
	    hop = 1;
	    found = 0;
	    visited[src] = src;
	    Queue q = newQueue();
	    QueueJoin(q, src);
	    while(!QueueIsEmpty(q)) {
	        Vertex v = QueueLeave(q);
	        for (i = 0; i < g->nV; i++) {
	            if (g->edges[i][v] < max && visited[i] == -1) {      
	                visited[i] = v;
	                if (i == dest) {
	                    found = 1;
	                    break;
	                }
	                else {
                        QueueJoin(q, i);
	                }
	            }
	        }
	    }
	    dropQueue(q);
	    // there is no route from src to dest
	    if (found == 0) {
	        hop = 0;
	    }
	    else {
	        i = dest;
	        while (visited[i] != src) {
	            path[hop - 1] = i;
	            hop++;
	            i = visited[i];
	        }
	        path[hop - 1] = i;
	        hop++;
	        path[hop - 1] = src;
	        
	        reversePath(path, hop);
        }
	}
	
	return hop; 
}

static void reversePath(int *a, int length) {
        int temp;
	    int start = 0;
	    int end = length - 1; 
        while (start < end) {
            temp = a[start];    
            a[start] = a[end]; 
            a[end] = temp; 
            start++; 
            end--; 
        }  

}

