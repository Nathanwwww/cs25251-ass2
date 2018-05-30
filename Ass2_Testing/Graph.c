// Graph ADT interface for Ass2 (COMP2521)
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Graph.h"
//============================================================================
//implement function
Graph newGraph(int noNodes);
void  insertEdge(Graph g, Vertex src, Vertex dest, int weight);
void  removeEdge(Graph g, Vertex src, Vertex dest);
bool  adjacent(Graph g, Vertex src, Vertex dest);
int   numVerticies(Graph g);
void  showGraph(Graph g);
void  freeGraph(Graph g);
AdjList outIncident(Graph g, Vertex v);
AdjList inIncident(Graph g, Vertex v);
//----------------------------------------------------------------------------
static void insertList(AdjList head,Vertex w, int weight);
//============================================================================
//init struct 
struct GraphRep{
	int nV;
    int nE;
    AdjList *edges;
}GraphRep;
//============================================================================
Graph newGraph(int noNodes) {
	 //debug
    assert(noNodes >= 0);

    Graph g = malloc(sizeof(Graph));
    g->nV = noNodes+1;
    g->nE = 0;
    g->edges = malloc(sizeof(AdjList)*noNodes);
    for(int i = 0;i < g->nV;i++){
        g->edges[i] = NULL;
    }
    
    return g;
}

int numVerticies(Graph g) {
    return g->nV;
}

void  insertEdge(Graph g, Vertex src, Vertex dest, int weight) {
	 //debug
    assert(g != NULL);

    //init 
    AdjList new = malloc(sizeof(AdjList));
    AdjList curr = g->edges[src];
    //init new edge
    new->w = dest;
    new->weight = weight;
    new->next = NULL;
    
    if (curr == NULL){
        g->edges[src] = new;
    }else if(!adjacent(g,src,dest)){
        while(curr->next != NULL){
            curr = curr->next;
        }
        curr->next = new;   
    }else{
        printf("Fail to insert edge\n");
        exit(1);
    }
    g->nE++;
}

void  removeEdge(Graph g, Vertex src, Vertex dest) {
    //debug
    assert(g != NULL);
    
    //init
    AdjList curr = g->edges[src];
    AdjList tmp;
   	while(curr->next != NULL){
       if(curr->next->w == dest){
           tmp = curr->next->next;
           free(curr->next);
           curr->next = tmp;
       	}
       	curr = curr->next;
   	}
    free(g->edges[src]);
}

bool adjacent(Graph g, Vertex src, Vertex dest) {
	AdjList curr = g->edges[src];
    while(curr != NULL){
        if(curr->w == dest) return true;
        curr = curr->next;
    }
    return false;
}

AdjList outIncident(Graph g, Vertex v) {
	//debug
    assert(g != NULL);
    if(v > g->nV){
        printf("try to access unavaible memory\n");
        exit(1);
    }
    
    
    if(g->edges[v] != NULL){
        return g->edges[v];
    } 
    return NULL;
}

AdjList inIncident(Graph g, Vertex v) {
	 //debug
    assert(g != NULL);
    AdjList list = NULL;
    if(v > g->nV){
        printf("try to access unavaible memory\n");
        exit(1);
    }

    for(int i = 0;i < g->nV;i++){
        AdjList curr = g->edges[i];
        while(curr != NULL){
            if(curr->w == v){
                insertList(list,i,curr->weight);
            }
            curr = curr->next;
        }
    }
    return list;
}

void  showGraph(Graph g) {
	assert(g != NULL);

    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);
    for (int i = 0; i < g->nV; i++) {
        AdjList curr = g->edges[i];
        while(curr != NULL){
            printf("%d, %d, %d\n",i,curr->w,curr->weight);
            curr = curr->next;
        }
    }
}

void  freeGraph(Graph g) {
 	assert(g != NULL);
    
    for (int i = 0; i < g->nV; i++){
        AdjList curr = malloc(sizeof(AdjList));
        curr = g->edges[i];
        AdjList tmp = malloc(sizeof(AdjList));
        while(curr != NULL){
            tmp = curr;
            curr = curr->next;
            free(tmp);
        }
    }
   free(g);
}

static void insertList(AdjList head,Vertex w, int weight){
    AdjList new = malloc(sizeof(AdjList));
    new->w = w;
    new->weight = weight;
    new->next = NULL;
    if(head == NULL){
        head = new;
        return;
    }
    while(head->next != NULL){
        head = head->next;
    }
    head->next = new;
}