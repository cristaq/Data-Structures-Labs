#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include <string.h>

typedef struct {
    unsigned char value;
    int left, right;
} HuffmanNode;

#define Item int

// Including below so `Item` is defined.
#include "heap.h"

void computeFreqs(char *text, int size, int freqs[256]) {
    for(int i = 0; i < 256; i++) {
        freqs[i] = 0;
    }
    for(int i = 0; i < size; i++) {
        freqs[(int)text[i]]++;
    }
}

HuffmanNode *makeTree(int freqs[256], int *size) {
    HuffmanNode *tree = malloc(256 * sizeof(HuffmanNode));
    *size = 0;
    int i;
    APriQueue queue = makeQueue(300);
    ItemType x;
    for(i = 0; i < 256; i++) {
        if(freqs[i] != 0) {
            tree[*size].value = (unsigned char)i;
            tree[*size].left = -1;
            tree[*size].right = -1;
            x.content = *size;
            x.prior = freqs[i];
            insert(queue, x);
            (*size)++;
        }
    }

    while (queue->size > 1) {
        ItemType a = removeMin(queue);
        ItemType b = removeMin(queue);
        ItemType newNode;
        tree[*size].value = '*';
        tree[*size].left = a.content;
        tree[*size].right = b.content;
        newNode.content = *size;
        newNode.prior = a.prior + b.prior;
        insert(queue, newNode);
        (*size)++;
    }
    
    free(queue);
    return tree;

}

void makeCodes(int index, HuffmanNode *nodes, char **codes, char *code) {
    if(nodes[index].left == -1 && nodes[index].right == -1) {
        strcpy(codes[(int)nodes[index].value], code);
    }
    else {
        strcat(code, "0");
        makeCodes(nodes[index].left, nodes, codes, code);
        code[strlen(code) - 1] = '\0';
        strcat(code, "1");
        makeCodes(nodes[index].right, nodes, codes, code);
        code[strlen(code) - 1] = '\0';
    }

}

char *compress(char *text, int textSize, HuffmanNode *nodes, int numNodes) {
    char *output = calloc(textSize * 10, sizeof(char));
    if(numNodes == 0) {
        return "hai cu tema 3";
    }
    else if(numNodes == 1) {
        while(textSize) {
            strcat(output, "~");
            textSize--;
        }
        return output;
    }
    char **codes = malloc(256 * sizeof(char*));
    for(int i = 0; i < 256; i++) {
        codes[i] = calloc(256, sizeof(char));
    }
    char *code = calloc(256, sizeof(char));
    makeCodes(numNodes - 1, nodes, codes, code);

    for(int i = 0; i < textSize; i++) {
        strcat(output, codes[(int)text[i]]);
    }

    for(int i = 0; i < 256; i++) {
        free(codes[i]);
    }
    free(codes);
    free(code);
    return output;
}

char *decompress(char *text, int textSize, HuffmanNode *nodes, int numNodes) {
    char *output = calloc(textSize * 10, sizeof(char));
    if(numNodes == 0) {
        return "";
    }
    else if(numNodes == 1) {
        for(int i = 0; i < textSize; i++) {
            output[i] = nodes[0].value;
        }
        return output;
    }
    char **codes = malloc(256 * sizeof(char*));
    for(int i = 0; i < 256; i++) {
        codes[i] = calloc(256, sizeof(char));
    }
    char *code = calloc(256, sizeof(char));
    makeCodes(numNodes - 1, nodes, codes, code);
    code[0] = '\0';
    int code_lenght = 0;
    int k = 0;

    for(int i = 0; i < textSize; i++) {
        code[code_lenght] = text[i];
        code[code_lenght + 1] = '\0';
        code_lenght++;
        for(int j = 0; j < 256; j++) {
            if(!strcmp(code, codes[j])) {
                output[k++] = (char)j;
                code_lenght = 0;
                code[0] = '\0';
                break;
            }
        }
    }

    for(int i = 0; i < 256; i++) {
        free(codes[i]);
    }
    free(codes);
    free(code);

    return output;
}

#endif
