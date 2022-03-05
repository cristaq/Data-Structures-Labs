#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>



typedef struct StackNode{
	Item elem;
	struct StackNode *next;
}StackNode;

typedef StackNode TCelSt; // Redenumirea unui nod la notatiile din curs 
typedef StackNode *ACelSt; // Redenumirea unui pointer la nod la notatiile din curs

typedef struct Stack{
	StackNode* head;  // Varful stivei
	long size; // Numarul de elemente din stiva
}Stack;

typedef Stack TStiva; // Redenumirea stivei la notatiile din curs
typedef Stack *ASt;//  // Redenumirea unui pointer la stiva la notatiile din curs

Stack* createStack(void){
	// TODO: Cerinta 1
	Stack *newStack = malloc(sizeof(Stack));
	newStack->head = NULL;
	newStack->size = 0; 
	return newStack;
}

int isStackEmpty(Stack* stack){
	// TODO: Cerinta 1
	if(stack->head == NULL)
		return 1;
	return 0;
}

void push(Stack *stack, Item elem){
	// TODO: Cerinta 1
	StackNode *newNode = malloc(sizeof(StackNode));
	newNode->elem = elem;
	newNode->next = stack->head;
	stack->head = newNode;
	stack->size++;
}

Item top(Stack *stack){	
	// TODO: Cerinta 1
	return stack->head->elem;
} 

void pop(Stack *stack){
	// TODO: Cerinta 1
	if(isStackEmpty(stack))
		return;
	StackNode *temp = stack->head;
	stack->head = stack->head->next;
	free(temp);
	stack->size--;
}

void destroyStack(Stack *stack){
	// TODO: Cerinta 1
	while(!isStackEmpty(stack)) {
		StackNode *temp = stack->head;
		stack->head = stack->head->next;
		free(temp);
	}
	free(stack);
}

#endif 
