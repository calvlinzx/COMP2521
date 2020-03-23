// Graph ADT interface for Ass2 (COMP2521)
#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

// array for all vertices in graph
int *visited;
static NodeValues *newCentrality(int numV);
static int numReachable(Graph g, Vertex src);
static bool hasPath(Graph g, Vertex src, Vertex dest);
static bool pathCheck(Graph g, Vertex src, Vertex dest);
static int count_paths(int s, int t, ShortestPaths *paths);
static double addbetweeness(Graph g, Vertex v);


NodeValues outDegreeCentrality(Graph g){
	int numV = numVerticies(g);
	NodeValues *outDegree = newCentrality(numV);
	int i;
   for (i = 0; i < numV; i++)
   {
	   AdjList L = outIncident(g, i);
	   AdjList count;
	   for (count = L; count != NULL; count = count->next)
	   {
	      outDegree->values[i] = outDegree->values[i] + 1;
	   }
	}
	
	return *outDegree;
}
NodeValues inDegreeCentrality(Graph g){
	int numV = numVerticies(g);
	NodeValues *inDegree = newCentrality(numV);
	int i;
   for (i = 0; i < numV; i++)
   {
	   AdjList L = inIncident(g, i);
	   AdjList count;
	   for (count = L; count != NULL; count = count->next)
	   {
	      inDegree->values[i] = inDegree->values[i] + 1;
	   }
	}
	
	return *inDegree;
}
NodeValues degreeCentrality(Graph g) {
	int numV = numVerticies(g);
	NodeValues *degreeCentrality = newCentrality(numV);
	
   for (int i = 0; i < numV; i++)
   {
	   AdjList L = outIncident(g, i);
	   AdjList count;
	   for (count = L; count != NULL; count = count->next)
	   {
	      degreeCentrality->values[i] = degreeCentrality->values[i] + 1;
	   }
	}
	
	for (int j = 0; j < numV; j++)
   {
	   AdjList L2 = inIncident(g, j);
	   AdjList count2;
	   for (count2 = L2; count2 != NULL; count2 = count2->next)
	   {
	      degreeCentrality->values[j] = degreeCentrality->values[j] + 1;
	   }
	}
	
	return *degreeCentrality;
}

NodeValues closenessCentrality(Graph g) {
	double closeness;
	int numV = numVerticies(g);
	NodeValues *centrality = newCentrality(numV);
	
	for (int i = 0; i < numV; i++) {
	    ShortestPaths paths = dijkstra(g, i);
	    int distSum = 0;
	    for (int j = 0; j < numV; j++) {
	        distSum = distSum + paths.dist[j];
	    }
	    int n = numReachable(g, i);
	    // to avoid 0 as denominator
       if (distSum == 0) {
	        closeness = 0;
	    }
	    else {
	        closeness = (double)(n*n)/((numV-1)*distSum);
	    }
	    centrality->values[i] = closeness;
	}
	
	return *centrality;
}

NodeValues betweennessCentrality(Graph g){
	int numV = numVerticies(g);
	NodeValues *betweeness = newCentrality(numV);
	
	for (int v = 0; v < numVerticies(g); v++) {
		betweeness->values[v] = addbetweeness(g, v);
	}
	return *betweeness;
}

NodeValues betweennessCentralityNormalised(Graph g){
	int numV = numVerticies(g);
	NodeValues *betweeness = newCentrality(numV);
	
	for (int v = 0; v < numVerticies(g); v++) {
		betweeness->values[v] = addbetweeness(g, v);
	}

   // normalizing betweeness
	int l = 0;
	while (l < numV)
	{
	   betweeness->values[l] = betweeness->values[l] / ((numV-1)*(numV-2));
	   l++;
	}
	return *betweeness;
}

void showNodeValues(NodeValues values){
    for (int i = 0; i < values.noNodes; i++) {
        printf("%d: %lf\n", i, values.values[i]);
    }
}

void freeNodeValues(NodeValues values){

    free(values.values);
}

//-------Helper function--------

// create and return a new NodeValues struct
static NodeValues *newCentrality(int numV) {
    NodeValues *new = malloc(sizeof(struct NodeValues));
    new->noNodes = numV;
    new->values = malloc(numV * sizeof(double));
    
    return new;
}

// count the number of vertex that src can reach
static int numReachable(Graph g, Vertex src) {
    int numV = numVerticies(g);   
    int count = 0;
    for (Vertex v = 0; v < numV; v++) {
        if (v != src && hasPath(g, src, v) == true) {
            count++;
        }
    }
    
    return count;
}

// return true if there is path from src to dest
static bool hasPath(Graph g, Vertex src, Vertex dest) {
    int numV = numVerticies(g);
    visited = malloc(numV * sizeof(int));
    
    for (Vertex v = 0; v < numV; v++) {
        visited[v] = -1;
    }
    visited[src] = src;
    return pathCheck(g, src, dest);
}

// check if there is path from v to dest using Depth-first search
static bool pathCheck(Graph g, Vertex v, Vertex dest) {
    int numV = numVerticies(g);
    for (Vertex w = 0; w < numV; w++) {
        if (adjacent(g, v, w) && visited[w] == -1) {
            visited[w] = v;
            if (w == dest) {
	            return true;
	        }
            else if (pathCheck(g, w, dest)) {
                return true;
            }
        }
    }
    return false;
}


// count how many shortest path from s to t
static int count_paths(int s, int t, ShortestPaths *paths) {
   int nPath = 0;
   for (PredNode *pred = paths->pred[t]; pred != NULL; pred = pred->next)
   {
      // if pred->v is not s, means there is still other paths
      if (pred->v != s)
      {
         nPath += count_paths(s, pred->v, paths);
      }
      else
      {
         nPath++;
      }
   }
   return nPath;
}

// calculate betweeness
static double addbetweeness(Graph g, Vertex v) {
   int numV = numVerticies(g);  
   double betweeness = 0;
   int all_Paths;
   ShortestPaths temp;
   ShortestPaths *paths;
   for (int s = 0; s < numV; s++)
   {
      if (s != v)
      {
         temp = dijkstra (g, s);
         paths = &temp;
         for (int t = 0; t < numV; t++)
         {
            if (t != v && t != s)
            {
               all_Paths = count_paths(s, t, paths);
               // no paths
               if (all_Paths == 0)
               {
                  betweeness += 0;
               }
               else
               {
                  betweeness += (double)(count_paths(s, v, paths))*(count_paths(v, t, paths))/all_Paths;
               }
            }
         }
      }
   }
   return betweeness;
}
