#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Util.h"
#include "Graph.h"

TGraphL* createGraphAdjList(int numberOfNodes) {
	//TODO: 1
	TGraphL *g = malloc(sizeof(TGraphL));
	g->nn = numberOfNodes;
	g->adl = malloc(numberOfNodes * sizeof(ATNode));
	for(int i = 0; i < numberOfNodes; i++)
		g->adl[i] = NULL;
	return g;
}

void addEdgeList(TGraphL* graph, int v1, int v2) {
	//TODO: 1
	ATNode newNode = malloc(sizeof(TNode));
	ATNode temp;
	newNode->v = v2;
	temp = graph->adl[v1];
	graph->adl[v1] = newNode;
	newNode->next = temp;

	newNode = malloc(sizeof(TNode));
	newNode->v = v1;
	temp = graph->adl[v2];
	graph->adl[v2] = newNode;
	newNode->next = temp;
}

List* dfsIterative(TGraphL* graph, int s) {
	//TODO: 2
	List *path = createList();
	int *visited = calloc(graph->nn, sizeof(int));
	Stack *stack = createStack();
	push(stack, s);
	visited[s] = 1;

	while(!isStackEmpty(stack)) {
		int element = top(stack);
		pop(stack);
		enqueue(path, element);
		
		ATNode p = graph->adl[element];
		while(p != NULL) {
			if(visited[p->v] == 0) {
				push(stack, p->v);
				visited[p->v] = 1;
			}
			p = p->next;
		}
	}

	destroyStack(stack);
	free(visited);
	return path;
}

void dfsRecHelper(TGraphL* graph, int* visited, List* path, int s) {
	//TODO: 3
	visited[s] = 1;
	enqueue(path, s);
	ATNode p = graph->adl[s];
	while(p != NULL) {
		if(visited[p->v] == 0) {
			dfsRecHelper(graph, visited, path, p->v);
		}
		p = p->next;
	}
}

List* dfsRecursive(TGraphL* graph, int s) {
	// TODO 3
	int *visited = calloc(graph->nn, sizeof(int));
	List *path = createList();
	dfsRecHelper(graph, visited, path, s);
	free(visited);
	return path;
}

List* bfs(TGraphL* graph, int s){
	// TODO: 4
	List *path = createList();
	int *visited = calloc(graph->nn, sizeof(int));
	Queue *queue = createQueue();
	enqueue(queue, s);
	visited[s] = 1;

	while(!isQueueEmpty(queue)) {
		int element = front(queue);
		dequeue(queue);
		enqueue(path, element);
		
		ATNode p = graph->adl[element];
		while(p != NULL) {
			if(visited[p->v] == 0) {
				enqueue(queue, p->v);
				visited[p->v] = 1;
			}
			p = p->next;
		}
	}

	destroyQueue(queue);
	free(visited);
	return path;
}


void destroyGraphAdjList(TGraphL* graph){
	// TODO: 5
	for(int i = 0; i < graph->nn; i++) {
		ATNode p = graph->adl[i];
		ATNode temp;
		while(p != NULL) {
			temp = p;
			p = p->next;
			free(temp);
		}
	}
	free(graph->adl);
	free(graph);

}

void removeEdgeList(TGraphL* graph, int v1, int v2){
	TNode* it = graph->adl[v1];
	TNode* prev = NULL;
	while(it != NULL && it->v != v2){
		prev = it;
		it = it->next;
	}

	if(it == NULL)return;

	if(prev != NULL)
		prev->next = it->next;
	else
		graph->adl[v1] = it->next;
	free(it);

	it = graph->adl[v2];
	prev = NULL;
	while(it != NULL && it->v != v1){
		prev = it;
		it = it->next;
	}
	if(it == NULL) return;
	if(prev != NULL)
		prev->next = it->next;
	else
		graph->adl[v2] = it->next;

	free(it);
}

void removeNodeList(TGraphL* graph, int v){
	for(int i = 0; i < graph->nn;i++){
		removeEdgeList(graph,v,i);
	}
}
