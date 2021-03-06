#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.h"

typedef int TCost;

typedef struct node
{
	int v;
	TCost c;
	struct node *next;
} TNode, *ATNode;

typedef struct
{
	int nn;
	ATNode *adl;
}	TGraphL;


void alloc_list(TGraphL * G, int n)
{
    int i;
    G->nn = n;
	G->adl = (ATNode*) malloc((n+1)*sizeof(ATNode));
	for(i = 0; i < n; i++)
		G->adl[i] = NULL;

}

void free_list(TGraphL *G)
{
    int i;
    ATNode it;
    for(i = 1; i < G->nn; i++){
		it = G->adl[i];
		while(it != NULL){
			ATNode aux = it;
			it = it->next;
			free(aux);
		}
		G->adl[i] = NULL;
	}
	G->nn = 0;
}

void insert_edge_list(TGraphL *G, int v1, int v2, int c)
{
 TNode *t;
 t=(ATNode)malloc(sizeof(TNode));
 t->v = v2; t->c=c; t->next = G->adl[v1]; G->adl[v1]=t;
 t=(ATNode)malloc(sizeof(TNode));
 t->v = v1;  t->c=c; t->next = G->adl[v2]; G->adl[v2]=t;
}


void dijkstra(TGraphL G, int s)
{
	MinHeap* h = newQueue(G.nn);
	h->size = G.nn;
	for(int i = 0; i < G.nn; i++) {
		h->elem[i] = malloc(sizeof(MinHeapNode));
		h->elem[i]->v = i;
		h->elem[i]->d = 10000;
		h->pos[h->elem[i]->v] = i;
	}
	h->elem[s]->d = 0;
	printf("\nDjikstra:\n");
	while(!isEmpty(h)) {
		MinHeapNode *min = removeMin(h);
		printf("nod %d cost %d\n", min->v, min->d);
		ATNode p = G.adl[min->v];
		while(p != NULL) {
			if(isInMinHeap(h, p->v)) {
				if(min->d + p->c < h->elem[h->pos[p->v]]->d) {
					h->elem[h->pos[p->v]]->d = min->d + p->c;
					SiftUp(h, p->v, h->elem[h->pos[p->v]]->d);
				}
			}
			p = p->next;
		}

	}
	printf("\n");

}

void Prim(TGraphL G)
{
	MinHeap* h = newQueue(G.nn);
	h->size = G.nn;
	for(int i = 0; i < G.nn; i++) {
		h->elem[i] = malloc(sizeof(MinHeapNode));
		h->elem[i]->v = i;
		h->elem[i]->d = 10000;
		h->pos[h->elem[i]->v] = i;
	}
	h->elem[0]->d = 0;
	printf("Prim:\n");
	while(!isEmpty(h)) {
		MinHeapNode *min = removeMin(h);
		printf("nod %d cost %d\n", min->v, min->d);
		ATNode p = G.adl[min->v];
		while(p != NULL) {
			if(isInMinHeap(h, p->v)) {
				if(p->c < h->elem[h->pos[p->v]]->d) {
					h->elem[h->pos[p->v]]->d = p->c;
					SiftUp(h, p->v, h->elem[h->pos[p->v]]->d);
				}
			}
			p = p->next;
		}

	}
}


int main()
{
    int i,v1,v2,c;
	int V,E;
	TGraphL G;
	ATNode t;
	freopen ("graph.in", "r", stdin);
	scanf ("%d %d", &V, &E);
	alloc_list(&G, V);

	for (i=1; i<=E; i++)
	{
		scanf("%d %d %d", &v1, &v2, &c);
	    insert_edge_list(&G, v1,v2, c);
	}

	for(i=0;i<G.nn;i++)
	{
    	printf("%d : ", i);
    	for(t = G.adl[i]; t != NULL; t = t->next)
   			 printf("%d ",t->v);
    		 printf("\n");
	}
	dijkstra(G,0);
	Prim(G);
	free_list(&G);

	return 0;
}