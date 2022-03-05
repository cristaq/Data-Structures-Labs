#include <stdio.h>

typedef int T;
#include "SortedList.h"

TSortedList getNaturals(int A, int B) {
    TSortedList nats = NULL;
    int i;
    for (i = A; i <= B; i++) {
        nats = insert(nats, i);
    }
    return nats;
}

TSortedList getPrimes(int N) {
    TSortedList nats = getNaturals(2, N);
    TSortedList p = nats;
    int i;
    while(!isEmpty(p)) {
        for(i = p->value * 2; i <= N; i += p->value)
            nats = deleteOnce(nats, i);
        p = p->next;
    }
    // TODO: Cerința Bonus

    return nats;
}

void printInts(TSortedList list) {
    while (!isEmpty(list)) {
        printf("%d ", list->value);
        list = list->next;
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    printInts(getPrimes(100));
    return 0;
}
