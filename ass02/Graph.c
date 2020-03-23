// Graph ADT interface for Ass2 (COMP2521)
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Graph.h"

struct GraphRep{
    AdjList *edges;
    int nV;
    int nE;
};

static bool inAdjL(AdjList L, Vertex n);
static adjListNode *newNode(Vertex n, int weight);
static AdjList insertAdjL(AdjList L, Vertex n, int weight);
static AdjList deleteAdjL(AdjList L, Vertex n);
static void showAdjL(AdjList L);
static void freeAdjL(AdjList L);

Graph newGraph(int noNodes) {
	assert(noNodes >= 0);
	
	// allocate memory for graph
	Graph g = malloc(sizeof(Graph));
	assert(g != NULL);
	g->nV = noNodes;
	g->nE = 0;
	
	// allocate memory for every list of every vertice
	g->edges = malloc(noNodes * sizeof(AdjList));
	assert(g->edges != NULL);
	for (int i = 0; i < noNodes; i++) {
	    g->edges[i] = NULL;
	}
	
	return g;
}

int numVerticies(Graph g) {
	
	return g->nV;
}

void insertEdge(Graph g, Vertex src, Vertex dest, int weight) {
	// check if the inputs are valid
	assert(g != NULL);
	assert(src >= 0 && src < g->nV);
	assert(dest >= 0 && dest < g->nV);	
	
	// if dest is not in the AdjList of src
	// insert that edge
	if (!inAdjL(g->edges[src], dest)) {
	    g->edges[src] = insertAdjL(g->edges[src], dest, weight);
	    g->nE++;
	}	
}

void removeEdge(Graph g, Vertex src, Vertex dest) {
    // check if the inputs are valid
	assert(g != NULL);
	assert(src >= 0 && src < g->nV);
	assert(dest >= 0 && dest < g->nV);
	
	// if dest is in the AdjList of src
	// delete that edge
	if (inAdjL(g->edges[src], dest)) {
	    g->edges[src] = deleteAdjL(g->edges[src], dest);
	    g->nE--;
	}
}

bool adjacent(Graph g, Vertex src, Vertex dest) {
	// check if the inputs are valid
	assert(g != NULL);
	assert(src >= 0 && src < g->nV);
	assert(dest >= 0 && dest < g->nV);
	
	return inAdjL(g->edges[src], dest);
}

AdjList outIncident(Graph g, Vertex v) {
	// check if the inputs are valid
	assert(g != NULL);
	assert(v >= 0 && v < g->nV);

	return g->edges[v];
}

AdjList inIncident(Graph g, Vertex v) {
	// check if the inputs are valid
	assert(g != NULL);
	assert(v >= 0 && v < g->nV);

	// create a new AdjList for vertices coming to V
	AdjList L = malloc(sizeof(AdjList));
	L = NULL;
	
	// traverse all the vertices in the graph
	for (int i = 0; i < g->nV; i++) {
		// traverse all the edges of the current vertex
        for (adjListNode *n = g->edges[i]; n != NULL; n = n->next) {
			// if the end point of current vertex is v
			// insert current vertex into the AdjList
	        if (n->w == v) {
	            L = insertAdjL(L, i, n->weight);
	        }
	    }
	}
	return L;
}

void  showGraph(Graph g) {
    assert(g != NULL);
    
    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);
    
    for (int i = 0; i < g->nV; i++) {
       printf("%d - ", i);
       showAdjL(g->edges[i]);
    }
}

void  freeGraph(Graph g) {
    assert(g != NULL);
    
    for (int i = 0; i < g->nV; i++)
      freeAdjL(g->edges[i]);

   free(g);
}

//---------Helper functions---------

// return true if vertex n is in AdjList L
static bool inAdjL(AdjList L, Vertex n) {
   if (L == NULL) {
      return false;
   }
   if (L->w == n) {
     return true;
   }

   return inAdjL(L->next, n);
}

// create and return a new adjListNode
static adjListNode *newNode(Vertex n, int weight) {
   adjListNode *new = malloc(sizeof(adjListNode));
   assert(new != NULL);
   new->w = n;
   new->weight = weight;
   new->next = NULL;
   return new;
}

// insert vertex n to AdjList L and return the AdjList
static AdjList insertAdjL(AdjList L, Vertex n, int weight) {
    adjListNode *new = newNode(n, weight);
    new->next = L;

    return new;
}

// delete vertex n from AdjList L and return the AdjList
static AdjList deleteAdjL(AdjList L, Vertex n) {
    if (L == NULL)
        return L;
    if (L->w == n)
        return L->next;

    L->next = deleteAdjL(L->next, n);
    return L;

}

// print the AdjList
static void showAdjL(AdjList L) {
   if (L == NULL)
      putchar('\n');
   else {
      printf("%d ", L->w);
      showAdjL(L->next);
   }
}

// free memory of the AdjList
static void freeAdjL(AdjList L) {
   if (L != NULL) {
      freeAdjL(L->next);
      free(L);
   }
}
