#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 256

typedef char Item;
#include "Stack.h"

int isBalanced(const char *str, int length){

  /* TODO: Cerinta 3
   * Implementation must use a stack.
   * Do NOT forget to deallocate the memory you use.
   */
    Stack *stack = createStack();
    int i = 0;
    while(i < length) {
      if(strchr("}])", str[i])) {
        if(isStackEmpty(stack) || top(stack) != str[i] - (1 + top(stack) % 2)) { //jonglerie cu ascii
          destroyStack(stack);
          return 0;
        }
        pop(stack);
      }
      else {
        push(stack, str[i]);
      }
      i++;
    }
    if(isStackEmpty(stack)) {
      destroyStack(stack);
      return 1;
    }
    destroyStack(stack);
    return 0;
      
}

int main(){
    int len;
    char buffer[MAX_INPUT_LEN];
    FILE* inputFile = fopen("input-parantheses.txt","r");
    if(inputFile == NULL) return 1;


    while(fgets(buffer, MAX_INPUT_LEN, inputFile) != NULL){
      buffer[strcspn(buffer, "\r\n")] = 0;
      len = strlen(buffer);
      if(len == 0) break;

      if(isBalanced(buffer, len))
        printf("%s ---> is balanced.\n", buffer);
      else
        printf("%s ---> not balanced.\n", buffer);
    }

    fclose(inputFile);

    return 0;
}
