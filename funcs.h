#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    char data;
    int freq;
    struct Node *left, *right;
};

typedef struct Node Node;

struct Heap
{
    Node **arr;
    int size;
    int capacity;
};

typedef struct Heap heap;

typedef struct
{
    char data;
    char code[32]; // Store the binary string (max 32-bit)
} HuffmanCode;

heap *createHeap(int capacity, Node **arr);
void heapifyUp(heap *h, int index);
void heapify(heap *h, int index);
Node *extractMin(heap *h);
void insert(heap *h, Node *node);
void printHeap(heap *h);

Node *newNode(char data, int freq);
Node *buildTree(char data[], int freq[], int size, int uniqueCount);
void generateCodes(Node *root, char *code, int depth, HuffmanCode huffmanTable[256]);

// Node *rebuildTree(FILE *compressedFile);
// void decodeData(FILE *compressedFile, Node *root, FILE *outputFile);
// void freeTree(Node *root);

#endif