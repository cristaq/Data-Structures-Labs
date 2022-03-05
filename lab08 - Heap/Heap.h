#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>

/* We assume there is a defined primitive type Item. */
typedef struct {
	int prior; // Item priority
	Item data; // Item d
}ItemType;

typedef struct heap{
	long maxHeapSize; // capacity
	long size; // number of elements
	ItemType *elem; // array of elements
} PriQueue, *APriQueue;


PriQueue* makeQueue(int maxHeapSize){
	//TODO:
	PriQueue *queue = malloc(sizeof(PriQueue));
	queue->maxHeapSize = maxHeapSize;
	queue->size = 0;
	queue->elem = malloc(maxHeapSize * sizeof(ItemType));
	return queue;
}

int getLeftChild(int i){
	//TODO:
	return 2 * i + 1;
}

int getRightChild(int i) {
	//TODO:
	return 2 * i + 2;
}

int getParent(int i) {
	//TODO:
	return (i - 1) / 2;
}

ItemType getMax(APriQueue h) {
	//TODO:
	return h->elem[0];
}

void siftUp(APriQueue h, int idx) {
	//TODO:
	while(idx >= 0 && h->elem[idx].prior > h->elem[getParent(idx)].prior) {
		ItemType aux;

		aux = h->elem[getParent(idx)];
		h->elem[getParent(idx)] = h->elem[idx];
		h->elem[idx] = aux;
		idx = getParent(idx);
	}

}


void insert(PriQueue *h, ItemType x) {
	//TODO:
	if(h->size == h->maxHeapSize) {
		h->maxHeapSize *= 2;
		h->elem = realloc(h->elem, h->maxHeapSize * sizeof(ItemType));
	}
	(h->size)++;
	h->elem[h->size - 1] = x;
	siftUp(h, h->size - 1);
}

void siftDown(APriQueue h, int idx){
	//TODO:
	int max;
	ItemType aux;
	while(getLeftChild(idx) < h->size || getRightChild(idx) < h->size) {
		
		if(getLeftChild(idx) < h->size && getRightChild(idx) < h->size) {
			max = h->elem[getLeftChild(idx)].prior > h->elem[getRightChild(idx)].prior ? getLeftChild(idx) : getRightChild(idx);	
		}
		else if(getLeftChild(idx) < h->size && getRightChild(idx) >= h->size) {
			max = getLeftChild(idx);
		}
		else if(getRightChild(idx) < h->size && getLeftChild(idx) >= h->size) {
			max = getRightChild(idx);
		}

		if(h->elem[idx].prior > h->elem[max].prior) {
			return;
		}
		aux = h->elem[max];
		h->elem[max] = h->elem[idx];
		h->elem[idx] = aux;
		idx = max;
	}
}

void removeMax(APriQueue h) {
	//TODO:
	ItemType aux;
	aux = h->elem[h->size - 1];
	h->elem[h->size - 1] = h->elem[0];
	h->elem[0] = aux;
	(h->size)--;
	siftDown(h, 0);
}

void freeQueue(APriQueue h){
	// TODO:
	free(h->elem);
	free(h);
}

#endif
