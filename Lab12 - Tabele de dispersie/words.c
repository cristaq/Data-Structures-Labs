#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* Key;
typedef int Value;
typedef long(*HashFunction)(Key, long);

typedef struct Element {
  Key key;
  Value value;
  struct Element *next;
} Element;

typedef struct HashTable {
  Element** elements;
  long size;
  HashFunction hashFunction;
} HashTable;

void initHashTable(HashTable **h, long size, HashFunction f) {
  // Cerinta 1
  *h = malloc(sizeof(HashTable));
  (*h)->elements = malloc(size * sizeof(Element*));
  (*h)->hashFunction = f;
  (*h)->size = size;
  for(int i = 0; i < size; i++) {
    (*h)->elements[i] = NULL;
  }
}

int exists(HashTable *hashTable, Key key) {
  // Cerinta 1
  int index = hashTable->hashFunction(key, hashTable->size);
  for(Element *p = hashTable->elements[index]; p != NULL; p = p->next) {
    if(!strcmp(p->key, key)) {
      return 1;
    }
  }
  return 0;
}

Value get(HashTable *hashTable, Key key) {
  // Cerinta 1
  int index = hashTable->hashFunction(key, hashTable->size);
  for(Element *p = hashTable->elements[index]; p != NULL; p = p->next) {
    if(!strcmp(p->key, key)) {
      return p->value;
    }
  }
  return (Value)0;
}

void put(HashTable *hashTable, Key key, Value value) {
  // Cerinta 1
  int index = hashTable->hashFunction(key, hashTable->size);
  if(exists(hashTable, key)) {
    for(Element *p = hashTable->elements[index]; p != NULL; p = p->next) {
      if(!strcmp(p->key, key)) {
        p->value = value;
        break;
      }
    }
  }
  else {
    Element *newElement = malloc(sizeof(Element));
    newElement->value = value;
    newElement->key = calloc(20, sizeof(char));
    strcpy(newElement->key, key);
    newElement->next = hashTable->elements[index];
    hashTable->elements[index] = newElement;
  }
}

void deleteKey(HashTable *hashTable, Key key) {
  // Cerinta 1
  int index = hashTable->hashFunction(key, hashTable->size);
  if(exists(hashTable, key)) {
    if(!strcmp(key, hashTable->elements[index]->key)) {
          Element* temp = hashTable->elements[index];
          hashTable->elements[index] = hashTable->elements[index]->next;
          free(temp);
          return;
      }
      Element *prev = hashTable->elements[index];
      Element *curr = hashTable->elements[index]->next;
      while(curr != NULL) {
        if(!strcmp(key, curr->key)) {
            prev->next = curr->next;
            free(curr->key);
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
      }
  }
}

void print(HashTable *hashTable) {
  // Cerinta 1
  for(int i = 0; i < hashTable->size; i++) {
    if(hashTable->elements[i] != NULL)
      printf("%d:\n", i);
    for(Element *p = hashTable->elements[i]; p != NULL; p = p->next) {
      printf("%s : %d\n", p->key, p->value);
    }
    if(hashTable->elements[i] != NULL)
      printf("\n");
  }
}

void freeHashTable(HashTable *hashTable) {
  // Cerinta 1
  for(int i = 0; i < hashTable->size; i++) {
    Element *temp;
    while(hashTable->elements[i] != NULL) {
        temp = hashTable->elements[i];
        hashTable->elements[i] = hashTable->elements[i]->next;
        free(temp->key);
        free(temp);
    }
  }
  free(hashTable->elements);
  free(hashTable);
}


long hash1(Key word, long size) {
  // Cerinta 2
  int h = 0;
  for(int i = 0; i < strlen(word) - 1; i++) {
    h = h * 17 + word[i];
  }
  return h % size;
}

int main(int argc, char* argv[]) {
  HashTable *hashTable;
  FILE *f1, *f2;
  char word[256];
  long hashSize, common = 0;

  hashSize = atoi(argv[1]);
  f1 = fopen(argv[2], "r");
  f2 = fopen(argv[3], "r");

  initHashTable(&hashTable, hashSize, &hash1);

  // Cerinta 3
  char *ceva = calloc(100, sizeof(char));
  while(fgets(ceva, 100, f1) != NULL) {
    char *p = strtok(ceva, " ");
    while(p != NULL) {
      int indice = get(hashTable, p);
      put(hashTable, p, indice + 1);
      p = strtok(NULL, " \n");
    }
  }

  print(hashTable);
  // ...

  // Cerinta 4
  while(fgets(ceva, 100, f2) != NULL) {
    char *p = strtok(ceva, " ");
    while(p != NULL) {
      int indice = get(hashTable, p);
      if (exists(hashTable, p) && indice) {
        common++;
        put(hashTable, p, indice - 1);
      }
      p = strtok(NULL, " \n");
    }
  }
  // ...
  free(ceva);
  freeHashTable(hashTable);
  printf("Common words: %ld\n", common);

  fclose(f1);
  fclose(f2);
  return 0;
}
