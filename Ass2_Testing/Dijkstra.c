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
static void insertNode(ShortestPaths path,Vertex w,Vertex v);
//============================================================================
ShortestPaths dijkstra(Graph g, Vertex v) {
	//debug
	assert( g != NULL);

	//init
	ShortestPaths path = initPath(g,v);
	PQ pq = newPQ();
	ItemPQ src;
	//insert src
	src.key = v;
	src.value = 0;
	addPQ(pq,src);

	while(!PQEmpty(pq)){
		ItemPQ curr = dequeuePQ(pq);
		int node = curr.key;
		AdjList list = outIncident(g,node);

		while(list != NULL){
			ItemPQ cur;
			cur.key = list->w;
			cur.value = list->weight;

			int dist = list->weight + path.dist[node];
			if(dist < path.dist[list->w]){
				path.dist[list->w] = dist;
				insertNode(path,list->w,node);	
			}
			addPQ(pq,cur);
			list = list->next;
		}
			
	}

	return path;
}

void showShortestPaths(ShortestPaths paths) {
	
}


void  freeShortestPaths(ShortestPaths paths) {
	free(paths.dist);
	for(int i = 0;paths.pred[i] != NULL;i++){
		PredNode *curr = paths.pred[i];
		PredNode *pre;
		while(curr != NULL){
			pre = curr;
			curr = curr->next;
			free(pre);
		}
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
		}
		new.dist[i] = INF; 
		new.pred[i] = NULL;
	}
	return new;
}

static void insertNode(ShortestPaths path,Vertex w,Vertex v){
	if(path.pred[w] == NULL){
		path.pred[w]->v = v;
		path.pred[w]->next = NULL;
	}else{
		PredNode *new = malloc(sizeof(PredNode));
		PredNode *curr = path.pred[w];
		new->v = v;
		new->next = NULL;
		while(curr->next != NULL){
			curr = curr->next;
		}
		curr->next = new;
	}
}

