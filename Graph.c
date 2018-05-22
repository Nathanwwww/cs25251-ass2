//cs2521 ass


//===========================================================================
//function need to be implemented 
Graph newGraph(int noNodes);
void  insertEdge(Graph g, Vertex src, Vertex dest, int weight);
void  removeEdge(Graph g, Vertex src, Vertex dest);
bool  adjacent(Graph g, Vertex src, Vertex dest);
int  numVerticies(Graph g);
//===========================================================================
Graph newGraph(int noNodes){
    assert (nV >= 0);

    Graph new = malloc(sizeof(Graph));
    assert(new != NULL);
    new->nV = noNodes;
    new->nE = 0;

    new->edges = malloc(sizeof(AdjList)*noNodes);
    assert(new->edges != NULL);
    for(int i = 0;i < noNodes;i++){
        new->edges[i] = NULL;
    }
    return new;
}
void insertEdge(Graph g, Vertax src, Vertax dest, int weight){
    //debug
    assert(g != NULL);
    
    //init var
    AdjList start = malloc(sizeof(AdjList));
    AdjList end = malloc(sizeof(AdjList));

    //function
    //create edges
    start->w = src;
    start->weight = weight;
    start->next = end;

    end->w = dest;
    end->weight = weight;
    end->next = NULL;
    
    //insert edge into array
    g->edges[src] = start;
    g->edges[dest] = end;
    g->nE++;
}

void removeEdges(Graph g, Vertax src, Vertax dest){
    //debug 
    assert(g != NULL);
    if(g->edges[src] == NULL || g->edges[dest] == NULL){
        fprintf(stderr,"Cannot find edge");
        exit(1);
    }

    //remove edge
    free(g->graph[src]);
    g->graph[src] = NULL;

    free(g->graph[dest]);
    g->graph[dest] = NULL;

}

bool adjacent(Graph g, Vertex src, Vertex dest){
    assert(g != NULL);
    
    AdjList next;
    next = g->edges[src]->next;
    if(next->nV == dest){
        return True;
    }else{
        return False;
    }
} 


