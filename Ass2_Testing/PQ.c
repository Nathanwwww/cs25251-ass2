// PQ ADT interface for Ass2 (COMP2521)
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define INF 99999
//=====================================================================================
PQ newPQ();
int PQEmpty(PQ p);
void addPQ(PQ pq, ItemPQ element);
ItemPQ dequeuePQ(PQ pq);
void updatePQ(PQ pq, ItemPQ element);
void  showPQ(PQ pq);
void  freePQ(PQ pq);
//=====================================================================================
struct PQRep {
	int capacity;
	int size;
	ItemPQ **index;
	ItemPQ *heap;
};
//--------------------------------------------------------------------------------------
//personal function
static void initArray(PQ pq,ItemPQ element);
static void sortHeap(PQ pq);
//---------------------------------------------------------------------------------------
PQ newPQ() {
	PQ new;
	new = malloc(sizeof(PQ));
	assert(new != NULL);
	new->capacity = 1000*sizeof(PQ);
	new->size = 0;
	new->index = malloc(sizeof(ItemPQ)*new->capacity);//store element according to order of key
	new->heap = malloc(sizeof(ItemPQ)*new->capacity);
	for(int i = 0; i < new->capacity;i++){
		new->index[i] = NULL;
		new->heap[i].key = i;
		new->heap[i].value = INF;
	}
	
	return new;

}

int PQEmpty(PQ pq) {
	if(pq->size == 0){
		return 1;
	}
	return 0;
}

void addPQ(PQ pq, ItemPQ element) {
	//debug 
	assert(pq != NULL);

	//init
	initArray(pq,element);
	//then matain a heap in heap[],min value at top of heap
	sortHeap(pq);
}

ItemPQ dequeuePQ(PQ pq) {
	//debug
	assert(pq != NULL);

	//init
	ItemPQ min = pq->heap[0];
	ItemPQ tmp;
	//init pq->heap[0] and pq->index[]
	pq->heap[0].value = INF;
	pq->index[min.key] = NULL;
	pq->heap[0].key = -1;
	tmp = pq->heap[pq->size-1];
	pq->heap[pq->size-1] = pq->heap[0];
	pq->heap[0] = tmp;
	pq->size = pq->size - 1;
	sortHeap(pq);
	return min;
}

void updatePQ(PQ pq, ItemPQ element) {
	//---
	assert(pq != NULL);

	int key = element.key; 
	if(pq->index[key] == NULL){
		return;
	}
	pq->index[key]->value = element.value;
}

void  showPQ(PQ pq) {
	int size = pq->size;
	printf("===============\n");
	printf("size: %d\n",size);
	for(int i = 0;pq->heap[i].value != INF ;i++){
		printf("key: %d value: %d\n",pq->heap[i].key,pq->heap[i].value);
	}
	printf("================\n");
}

void  freePQ(PQ pq) {
	free(pq->heap);
	for(int i = 0; i < pq->capacity;i++){
		free(pq->index[i]);
		pq->index[i] = NULL;
	}
	free(pq->index);
	free(pq);
}
//------------------------------------------------------------------------
static void initArray(PQ pq,ItemPQ element){
	int index = pq->size;
	int key = element.key;

	pq->heap[index] = element;
	pq->index[key] = &element;
	pq->size++;
}

static void sortHeap(PQ pq){
	int index = pq->size - 1;
	ItemPQ tmp;
	while((index-1)/2 >= 0){
		//if parent node value is greater than child node ,swap
		if(pq->heap[(index-1)/2].value > pq->heap[index].value){
			tmp = pq->heap[index];
			pq->heap[index] = pq->heap[(index-1)/2];
			pq->heap[(index-1)/2] = tmp; 
		}
		index--;
	}
}