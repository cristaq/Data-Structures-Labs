#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <stdlib.h>
#include <assert.h>

/*
    IMPORTANT!

    As we stick to pure C, we cannot use templates. We will just asume
    some type T was previously defined.
*/

// -----------------------------------------------------------------------------

typedef struct node {
    T value;
    struct node* next;
} TNode, *TSortedList;

// TODO : Cerința 1 & Cerința 2

TSortedList create(T value) {
    // TODO (se va completa la Cerința 2)
    TSortedList node = malloc(sizeof(TNode));
    node->value = value;
    node->next = NULL;
    return node;
}

int isEmpty(TSortedList list) {
    if(list == NULL)
        return 1;
    return 0;
}

int contains(TSortedList list, T elem) {
    TSortedList p = list;
    while(p != NULL) {
        if(p->value == elem)
            return 1;
        p = p->next;
    }
    return 0;
}

TSortedList insert(TSortedList list, T elem) {
    TSortedList newNode = create(elem);
    if(list == NULL)
        return newNode;
    if(elem < list->value) {
        newNode->next = list;
        return newNode;
    }
    TSortedList prev = list;
    TSortedList curr = list->next;
    while(curr != NULL) {
        if(elem < curr->value) {
            newNode->next = curr;
            prev->next = newNode;
            return list;
        }
        prev = curr;
        curr = curr->next;
    }
    prev->next = newNode;
    return list;
}

TSortedList deleteOnce(TSortedList list, T elem) {
    if(elem == list->value) {
        TSortedList temp = list;
        list = list->next;
        free(temp);
        return list;
    }
    TSortedList prev = list;
    TSortedList curr = list->next;
    while(curr != NULL) {
        if(elem == curr->value) {
            prev->next = curr->next;
            free(curr);
            return list;
        }
        prev = curr;
        curr = curr->next;
    }
    return list;
}

long length(TSortedList list){
    TSortedList p = list;
    long len = 0;
    while(p != NULL) {
        len++;
        p = p->next;
    }
    return len;
}

T getNth(TSortedList list, int n){
    TSortedList p = list;
    while(n - 1) {
        p = p->next;
        n--;
    }
    return p->value;
}

TSortedList freeTSortedList(TSortedList list) {
    TSortedList temp;
    while(list != NULL) {
        temp = list;
        list = list->next;
        free(temp);
    }
    return list;
}


#endif
