#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

typedef int Item;

typedef struct QueueNode{
	Item elem;
	struct QueueNode *next;
}QueueNode;

typedef QueueNode TcelQ;
typedef QueueNode *ACelQ;

typedef struct Queue{
	QueueNode *front;
	QueueNode *rear;
	long size;
}Queue;

typedef Queue TCoada;
typedef Queue *AQ;


Queue* createQueue(void){
	// TODO: Cerinta 2
	Queue *newQueue = malloc(sizeof(Queue));
	newQueue->front = NULL;
	newQueue->rear = NULL;
	newQueue->size = 0;
	return newQueue;
} 

int isQueueEmpty(Queue *q){
	// TODO: Cerinta 2
	if(q->front == NULL || q->rear == NULL)
		return 1;
	return 0;
}

void enqueue(Queue *q, Item elem){
	// TODO: Cerinta 2
	QueueNode *newNode = malloc(sizeof(QueueNode));
	newNode->elem = elem;
	newNode->next = NULL;
	if(isQueueEmpty(q)) {
		q->front = newNode;
		q->rear = newNode;
		q->size++;
		return;
	}
	q->rear->next = newNode;
	q->rear = newNode;
	q->size++;
}

Item front(Queue* q){
	// TODO: Cerinta 2
	return q->front->elem;
}

void dequeue(Queue* q){
	// TODO: Cerinta 2
	if(isQueueEmpty(q))
		return;
	if(q->size == 1) {
		free(q->front);
		q->front = NULL;
		q->rear = NULL;
		q->size--;
		return;
	}
	QueueNode *temp = q->front;
	q->front = q->front->next;
	free(temp);
	q->size--;

}

void destroyQueue(Queue *q){
	// TODO: Cerinta 2
	while(!isQueueEmpty(q)) {
		QueueNode *temp = q->front;
		q->front = q->front->next;
		free(temp);
	}
	free(q);
}

#endif
