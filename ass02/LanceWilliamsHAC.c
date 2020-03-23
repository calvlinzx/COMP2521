/*Lance-Williams Algorithm for Agglomerative Clustering
  Written by 
  COMP2521 2019 T1
*/

#include <stdlib.h>
#include <stdio.h>
#include "LanceWilliamsHAC.h"
#include "Graph.h"

#define numVertices numVerticies
#define INFINITY 100000

static int compare(int a, int b, int method);
static Dendrogram newDendrogram(int v);
static void initialiseDist(int **dist, Graph g, int method);

/* 
 * Finds Dendrogram using Lance-Williams algorithm (as discussed in the specs) 
   for the given graph g and the specified method for agglomerative clustering.
   Method value 1 represents 'Single linkage', and 2 represents 'Complete linkage'.
   For this assignment, you only need to implement the above two methods. 

   The function returns 'Dendrogram' structure (binary tree) with the required information.
 * 
 */

Dendrogram LanceWilliamsHAC(Graph g, int method) {
	int numV = numVerticies(g);
	int inf;
	
	// Different inf due to different method
	if (method == 1) {
		inf = -1;
	}
	else if (method == 2) {
		inf = INFINITY;
	}

	// Allocate memory
	int **dist = malloc(numV * sizeof(int*));
	Dendrogram *dendA = malloc(numV * sizeof(Dendrogram));
	for (Vertex i = 0; i < numV; i++) {
		dist[i] = malloc(numV * sizeof(Vertex));
		dendA[i] = newDendrogram(i);
		for (Vertex j = 0; j < numV; j++) {
			dist[i][j] = inf;
		}
	}

	// Initialise dist table
	initialiseDist(dist, g, method);
	
	int size = numV;
	int src, dest, distance;
	while(size > 1) {
		src = dest = distance = inf;
		// Iterate the dist table to find the min or max
		for (int i = numV-1; i > 0; i--) {
			for (int j = i-1; j >= 0; j--) {
				if (compare(dist[i][j], distance, method)) {
					src = i;
					dest = j;
					distance = dist[i][j];
				}
			}
		}
		
		// Remove that distance in the table
		dist[src][dest] = inf;
		Dendrogram dendLeft = dendA[dest];
		Dendrogram dendRight = dendA[src];

		// while the node does not point itself or not point the joint
		// The node will point to where the node merged into, jump to that node
		int mergeout = src; 
		while (dendRight->vertex != src && dendRight->vertex != inf) {
			mergeout = dendRight->vertex;
			dendRight = dendA[mergeout];
		}

		int mergein = dest; 
		while (dendLeft->vertex != dest && dendLeft->vertex != inf) {
			mergein = dendLeft->vertex;
			dendLeft = dendA[mergein];
		}

		// Two nodes are in the same cluster after merging
		if (dendLeft == dendRight) {
			continue;
		}
		// Merge two clusters from right to left
		if (mergein > mergeout) {
			int tmp = mergein;
			mergein = mergeout;
			mergeout = tmp;
		}

		Dendrogram newCluster = newDendrogram(inf);
		newCluster->left = dendLeft;
		newCluster->right = dendRight;
		dendA[mergein] = newCluster;
		dendA[mergeout] = newDendrogram(mergein);
		size--;
	}

	// Root dendrogram which is going to be returned
	Dendrogram dendRoot = dendA[0];
	
	// Free memory 
	for (int i = 0; i < numV; i++)  {
		free(dist[i]);
		if (i > 0) {
			freeDendrogram(dendA[i]);
		}
	}
	free(dist);
	return dendRoot;
}

void freeDendrogram(Dendrogram d) {
    if (d->left == NULL && d->right == NULL) {
        free(d);
    }
    else {
        freeDendrogram(d->left);
        freeDendrogram(d->right);
    }
}

//--------Helper Functions----------

// create and return new Denfrogram struct
static Dendrogram newDendrogram(int v){
	Dendrogram new = malloc(sizeof(Dendrogram));
	new->left = new->right = NULL;
	new->vertex = v;
	return new;
}

// return a or b due to different methods
static int compare(int a, int b, int method){
	if (method == 1) {
			return (a > b);
	}
	if (method == 2){
			return (a < b);
	}
	return -1;
}

// set up the distance matrix
static void initialiseDist(int **dist, Graph g, int method) {
	int numV = numVerticies(g);
	for (Vertex src = 0; src < numV; src++) {
		AdjList curr = outIncident(g, src);
		while (curr != NULL) {
			Vertex dest = curr->w;
			dist[src][dest] = curr->weight;
			if (compare(dist[src][dest], dist[dest][src], method))
				dist[dest][src] = dist[src][dest];
			else dist[src][dest] = dist[dest][src];
		curr = curr->next;			
		}
	}

}


