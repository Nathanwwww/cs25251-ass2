// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <limits.h>

#define INF 99999
//===========================================================================
ShortestPaths dijkstra(Graph, Vertex);
void  showShortestPaths(ShortestPaths);
void  freeShortestPaths(ShortestPaths);
//----------------------------------------------------------------------------
//personal function
static ShortestPaths initPath(Graph g, Vertex v);
//static void insertNode(ShortestPaths path,Vertex w,Vertex v);
//============================================================================
ShortestPaths dijkstra(Graph g, Vertex v) {
	//debug
	assert( g != NULL);

	//init
	ShortestPaths path = initPath(g,v);
	PQ pq = newPQ();
	int visted[numVerticies(g)];
	for(int i = 0;i < numVerticies(g);i++){
		visted[i] = 0;
	}
	//step 1: create a start node and insert it into heap
	//value = 0;which means it is a start node
	ItemPQ src;
	src.key = v;
	src.value = 0;

	addPQ(pq,src);
	
	
	while(!PQEmpty(pq)){
		//if a node has been visted , do not add it into heap
		ItemPQ curr = dequeuePQ(pq);
		int currVertex = curr.key;
		AdjList edgeList = outIncident(g,currVertex);
		if(visted[currVertex] == 0){
			visted[currVertex] = 1;		//set to 1: this node has been visted 
		}else{
			continue;					//if this node has been visted, then jump this heap to next unvisted node
		}

		while(edgeList != NULL){
			//if v has not been visted , add it to heap
			ItemPQ edges;
			edges.key = edgeList->w;
			edges.value = edgeList->weight;

			addPQ(pq,edges); // add it to heap

			if(edgeList->weight + path.dist[currVertex] < path.dist[edgeList->w]){
				//swap
				PredNode *node = malloc(sizeof(PredNode));
				node->v = currVertex;
				node->next = NULL;
				
				path.dist[edgeList->w] = edgeList->weight + path.dist[currVertex];
				path.pred[edgeList->w] = node;
			}
			
			edgeList = edgeList->next;
		}
	}
	for(int i = 0; i < path.noNodes; i++){
		if(path.dist[i] == INF){
			path.dist[i] = 0;
		}
	}
	return path;
}

void showShortestPaths(ShortestPaths paths) {
	
}


void  freeShortestPaths(ShortestPaths paths) {
	free(paths.dist);
	for(int i = 0;i < paths.noNodes;i++){
		free(paths.pred[i]);
	}
	free(paths.pred);
	
}

//===============================================================================
static ShortestPaths initPath(Graph g, Vertex v){
	ShortestPaths new;
	new.noNodes = numVerticies(g);
	new.src = v;
	new.dist = malloc(sizeof(int)*new.noNodes);
	new.pred = malloc(sizeof(PredNode)*new.noNodes);
	
	for(int i = 0;i < new.noNodes;i++){
		if(i == v){
			new.dist[i] = 0;
		}else{
			new.dist[i] = INF; 
		}
		new.pred[i] = NULL;
	}
	return new;
}



