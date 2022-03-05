#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_
#include <stdlib.h>
/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------
/**
 *  Linked list representation -- R2 Curs2 (Slide 8)
 */
typedef struct ListNode{
	Item elem; // Stored node value
	struct ListNode* next; // link to next node
	struct ListNode* prev; // link to prev node
} ListNode;

/**
 *  Double linked list representation -- desen Curs 3 (Slide 19)
 */
typedef struct List{
	ListNode* first; // link to the first node
	ListNode* last; // link to the last node
}List;
// -----------------------------------------------------------------------------

/**
 * Create a new node
 *  [input]: Item
 *  [output]: List*
 */
ListNode *createNode(Item elem) {
	// TODO: Cerinta 1a
	ListNode *newnode = malloc(sizeof(ListNode));
	newnode->elem = elem;
	newnode->next = NULL;
	newnode->prev = NULL;
	return newnode;
}

/**
 * Create a new (empty)  list  -- Silde-urile 13/14 Curs 2
 *  [input]: None
 *  [output]: List*
 */
List* createList(void){
	// TODO: Cerinta 1a
	List *list = malloc(sizeof(List));
	list->first = NULL;
	list->last = NULL;
	return list;
}
// -----------------------------------------------------------------------------


/**
 * Determines if the list is empty
 *  [input]: List*
 *  [output]: 1 - empty/ 0 - not empty
 */
int isEmpty(List *list){
	// TODO: Cerinta 1b
	if(list->first == NULL && list->last == NULL)
		return 1;
	return 0;
}
// -----------------------------------------------------------------------------


/**
 * Determines if a list contains a specified element
 *  [input]: List*, Item
 *  [output]: int (1 - contains/ 0 - not contains)
 */
int contains(List *list, Item elem){
	// TDOO: Cerinta 1c
	ListNode *p = list->first;
	while(p != NULL) {
		if(p->elem == elem)
			return 1;
		p = p->next;
	}
	return 0;
}
// -----------------------------------------------------------------------------

/**
 * Compute list length
 *  [input]: List*
 *  [output]: int
 */
int length(List *list){
	// Guard against young player errors
	if(list == NULL) return 0;

	// TODO: Cerinta 1f
	ListNode *p = list->first;
	int i = 0;
	while(p != NULL) {
		i++;
		p = p->next;
	}
	return i;
}
// -----------------------------------------------------------------------------


/**
 * Insert a new element in the list at the specified position.
 * Note: Position numbering starts with the position at index zero
 *  [input]: List*, Item, int
 *  [output]: void
 */
void insertAt(List* list, Item elem, int pos){

	// Guard against young player errors
	int len = length(list);
	if(list == NULL) return;
	if(pos < 0 || pos > len) return;
	ListNode *newnode = createNode(elem);

	// TODO: Cerinta 1d
	if(isEmpty(list)) {
		list->first = newnode;
		list->last = newnode;
		return;
	}
	if(pos == 0) {
		newnode->next = list->first;
		list->first->prev = newnode;
		list->first = newnode;
		return;
	}
	if(pos == len) {
		list->last->next = newnode;
		newnode->prev = list->last;
		list->last = newnode;
		return;
	}
	//cazul cand inserez in "centru"
	ListNode *p = list->first;
	while(pos) {
		p = p->next;
		pos--;
	}
	newnode->next = p;
	newnode->prev = p->prev;
	p->prev->next = newnode;
	p->prev = newnode;
	return;

}
// -----------------------------------------------------------------------------


/**
 * Delete the first element instance form a list.
 *  [input]: List*, Item
 *  [output]: void
 */
void deleteOnce(List *list, Item elem){
	// Guard against young player errors
	if(list == NULL) return;
	if(isEmpty(list)) return;

	if(length(list) == 1) {
		free(list->first);
		list->first = NULL;
		list->last = NULL;
		return;
	}

	if(list->first->elem == elem) {
		list->first = list->first->next;
		free(list->first->prev);
		list->first->prev = NULL;
		return;
	}
	if(list->last->elem == elem) {
		list->last = list->last->prev;
		free(list->last->next);
		list->last->next = NULL;
		return;
	}

	ListNode *p = list->first;
	while(p != NULL) {
		if(p->elem == elem) {
			p->prev->next = p->next;
			p->next->prev = p->prev;
			free(p);
			return;
		}
		p = p->next;
	}
	return;


	//TODO: Cerinta 1e
}
// -----------------------------------------------------------------------------


/**
 * Destroy a list.
 *  [input]: List*
 *  [output]: void
 */
List* destroyList(List* list){
	// Guard against young player errors
	if(list == NULL) return NULL;

	//TODO: Cerinta 1g
	while(list->first != list->last) {
		list->first = list->first->next;
		free(list->first->prev);
	}
	free(list->last);
	free(list);
	return NULL;
}
// -----------------------------------------------------------------------------


#endif //_DOUBLE_LINKED_LIST_H_
