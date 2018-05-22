//Graph ADT interface for Ass2(comp2521)
#include "Graph.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
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
//============================================================================
//personal function

//============================================================================
Graph newGraph(int noNodes){
    //debug
    assert(noNodes >= 0);

    Graph g = malloc(sizeof(Graph));
    g->nV = noNodes;
    g->nE = 0;
    g->edges = malloc(sizeof(AdjList)*noNodes);
    for(int i = 0;i < g->nV;i++){
        g->edges[i] = NULL;
    }
    return g;
}

void insertEdge(Graph g, Vertex src, Vertex dest, int weight){
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
        curr = new;
    }else if(!adjacent(g,src,dest)){
        while(curr->next != NULL){
            curr = curr->next;
        }
        curr->next = new;   
    }else{
        printf("Fail to insert edge\n");
        exit(1);
    }
}

void removeEdge(Graph g, Vertex src, Vertex dest){
    //debug
    assert(g != NULL);
    
    //init
    AdjList curr = g->edges[src];
    AdjList next;
    
   while(curr != NULL){
       if(curr->w == dest){
           next = curr->next;
           free(curr);
       }
       curr = curr->next;
   }
}

bool adjacent(Graph g, Vertex src, Vertex dest){
    AdjList curr = g->edges[src];
    while(curr != NULL){
        if(curr->w == dest) return 1;
        curr = curr->next;
    }
    return 0;
}

int numVerticies(Graph g){
    return g->nV;
}
AdjList outIncident(Graph g, Vertex v){
    //debug
    assert(g != NULL);

    AdjList list[g->nV];
    int index = 0;

    AdjList curr = g->edges[v];
    while(curr != NULL){
        list[index] = curr;
        index++;
        curr = curr->next;
    }
    return list;
}
AdjList inIncident(Graph g, Vertex v){
    //debug
    assert(g != NULL);
    
    int index = 0;
    AdjList list[g->nV];
    
    for(int i = 0;i < g->nV;i++){
        AdjList curr = g->edges[i];
        while(curr != NULL){
            if(curr->w == v){
                list[index] = curr;
                index++;
            }
            curr = curr->next;
        }
    }
    return list;
}
void  showGraph(Graph g){
    assert(g != NULL);

    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);
    for (int i = 0; i < g->nV; i++) {
        AdjList curr = g->edges[i];
        while(curr != NULL){
            printf("%d ----> %d(weight: %d)\n",i,curr->w,curr->weight);
            curr = curr->next;
        }
    }
}
void  freeGraph(Graph g){
    assert(g != NULL);
    
    for (int i = 0; i < g->nV; i++){
        AdjList curr = g->edges[i];
        AdjList tmp;
        while(curr != NULL){
            tmp = curr;
            curr = curr->next;
            free(tmp);
        }
    }
   free(g);
}

//=============================================================================================
//personal function



