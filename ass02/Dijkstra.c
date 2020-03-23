// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#define INFINITY 100000 

static PredNode *replacePred(PredNode *p, int v);
static PredNode *insertPred(PredNode *p, int v);
static struct PredNode *newNode(int v);
static ItemPQ newItem(int key, int value);

ShortestPaths dijkstra(Graph g, Vertex v) {
	// allocate memory and initialise
    ShortestPaths path;
	int numV = numVerticies(g);
	int visited[numV];
	path.noNodes = numV;
    path.src = v;
    path.dist = malloc(numV * sizeof(int));
    path.pred = malloc(numV * sizeof(struct PredNode));
	PQ pq = newPQ();
	
    // set up the initial path, visited array and pq
	for (int i = 0; i < numV; i++) {
	    if (i == v) {
	        path.dist[i] = 0;
	        // mark src as visited
            visited[i] = 0;
	    }
	    else {
	        path.dist[i] = INFINITY;
            // mark other vertices as unvisited
            visited[i] = -1;  
	    }
	    path.pred[i] = NULL;
	    ItemPQ new = newItem(i, path.dist[i]);
	    addPQ(pq, new);  
	}
	
    // while there is still element in pq
	while (PQEmpty(pq) == 1) {
	    ItemPQ curr = dequeuePQ(pq);
	    AdjList edge = outIncident(g, curr.key);
	    
	    while (edge != NULL) {
	        // if the end point of current edge has not been visited yet
            if (visited[edge->w] == -1) {
                // if the new distance is shorter than current distance
	            if (path.dist[curr.key] + edge->weight < path.dist[edge->w]) {
	                // update the current distance to new distance
                    path.dist[edge->w] = path.dist[curr.key] + edge->weight;
	                // update the predecessor list
                    path.pred[edge->w] = replacePred(path.pred[edge->w] ,curr.key);
                    // update pq
                    ItemPQ dest = newItem(edge->w, path.dist[edge->w]);
                    updatePQ(pq, dest);
                    // mark current vertex as visited
                    visited[curr.key] = 0;
                }
                // if new distance is the same as current distance          
                else if (path.dist[curr.key] + edge->weight == path.dist[edge->w]) {
                    // insert current to the predecessor list
                    path.pred[edge->w] = insertPred(path.pred[edge->w] ,curr.key);
                }
	        }
	        edge = edge->next;
	    } 
	}
    // free pq
	free(pq);
	
	for (int i = 0; i < path.noNodes; i++) {
	    // if there is no path from vertex v to vertex i
        // set the distance to 0
        if (path.pred[i] == NULL) {
	        path.dist[i] = 0;
	    }
	}
	
	return path;
}

void showShortestPaths(ShortestPaths paths) {
    printf("The shortest distance array for %d is:\n", paths.src);
    for (int i = 0; i < paths.noNodes; i++) {
        printf("%d: %d", i, paths.dist[i]);
    }
    printf("The previous node array for %d is:\n", paths.src);
    for (int i = 0; i < paths.noNodes; i++) {
        printf("%d: %p", i, paths.pred[i]);
    }

}


void  freeShortestPaths(ShortestPaths paths) {
    free(paths.dist); //free the distance array
    int i = 0;
    while (i < paths.noNodes) { 
        free(paths.pred[i]);
        i++;
    }
    free(paths.pred);
}

//-----------Helper functions-----------

// create and return a new PredNode
static struct PredNode *newNode(int v) {
   struct PredNode *new = malloc(sizeof(struct PredNode));
   assert(new != NULL);
   new->v = v;
   new->next = NULL;
   return new;
}

// replace the current node with the new one
static PredNode *replacePred(PredNode *p, int v) {
    PredNode *new = newNode(v);
    if (p != NULL) {
        free(p);
    }
    new->next = NULL;
    return new;
}

// insert the new node before the current one
static PredNode *insertPred(PredNode *p, int v) {
    PredNode *new = newNode(v);
    new->next = p;

    return new;
}

// create and return a new ItemPQ
static ItemPQ newItem(int key, int value) {
    ItemPQ *new = malloc(sizeof(ItemPQ));
    new->key = key;
    new->value = value;
    return *new;
}
