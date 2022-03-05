#include <stdio.h>
#include <string.h>

typedef long T;
#include "OrderedSet.h"

OrderedSet* multipli(int a, int b, int nr) {
    OrderedSet* set = createOrderedSet(b);
    T i;
    for(i = (a / nr + 1) * nr; i <= b; i += nr) {
        set->elements[set->size] = i;
        set->size++;
    }
    return set;
}

void afis(OrderedSet* set) {
    int i;
    printf("There are %ld elemnts:", set->size);
    for(i = 0; i < set->size; i++)
        printf(" %ld", set->elements[i]);
    printf("\n");
}

int main(){
    OrderedSet* set1 = multipli(4, 25, 3);
    afis(set1);

    OrderedSet* set2 = multipli(5, 30, 4);
    afis(set2);

    OrderedSet* su = unionOrderedSets(set1, set2);
    afis(su);

    OrderedSet* si = intersectOrderedSets(set1, set2);
    afis(si);
}