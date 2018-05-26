// PQ ADT interface for Ass2 (COMP2521)
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
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
	new->capacity = 4096;
	new->size = 0;
	new->index = malloc(sizeof(ItemPQ)*new->capacity);//store element according to order of key
	new->heap = malloc(sizeof(ItemPQ)*new->capacity);
	for(int i = 0; i < new->capacity;i++){
		new->index[i] = NULL;
	}
	return new;

}

int PQEmpty(PQ pq) {
	if(pq->heap == NULL){
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
	if(pq->heap == NULL){
		fprintf(stderr,"heap is not exist\n");
		exit(1);
	}
	int lastNode = pq->size - 1;
	//remove heap[0],move heap[last] to heap[0],resort heap[]
	pq->heap[0] = pq->heap[lastNode];
	pq->size--;
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
	for(int i = 0;i < size;i++){
		printf("key: %d value: %d\n",pq->heap[i].key,pq->heap[i].value);
	}
}

void  freePQ(PQ pq) {
	free(pq->heap);
	free(pq->index);
	free(pq);
}
//------------------------------------------------------------------------
static void initArray(PQ pq,ItemPQ element){
	int i = element.key;
	int h = pq->size;
	if(pq->index[i] != NULL){
		pq->index[i]->value = element.value;
		return;
	}
	pq->index[i] = &element;
	pq->heap[h] = element;
	pq->size++;
}

static void sortHeap(PQ pq){
	int index = pq->size;
	ItemPQ tmp;
	while((index-1)/2 >= 0){
		if(pq->heap[(index-1)/2].value > pq->heap[index].value){
			tmp = pq->heap[index];
			pq->heap[index] = pq->heap[(index-1)/2];
			pq->heap[(index-1)/2] = tmp; 
		}
		index--;
	}
}