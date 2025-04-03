#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcs.h"

typedef struct
{
    char data;
    int freq;
} DataFreq;

int compare(const void *a, const void *b)
{
    DataFreq *dfA = (DataFreq *)a;
    DataFreq *dfB = (DataFreq *)b;

    return dfA->data - dfB->data;
}

Node *newNode(char data, int freq)
{
    Node *node = (Node *)malloc(sizeof(Node));

    node->data = data;
    node->freq = freq;
    node->left = node->right = NULL;

    return node;
}

Node *buildTree(char chars[], int freqs[], int size, int uniqueCount)
{
    DataFreq *dfArray = (DataFreq *)malloc(uniqueCount * sizeof(DataFreq));
    int c = 0;
    for (int i = 0; i < size; i++)
    {
        if (freqs[i] > 0)
        {
            dfArray[c].data = chars[i];
            dfArray[c].freq = freqs[i];
            c++;
        }
    }
    chars = (char *)malloc(uniqueCount * sizeof(char));
    freqs = (int *)malloc(uniqueCount * sizeof(int));

    qsort(dfArray, uniqueCount, sizeof(DataFreq), compare);

    for (int i = 0; i < uniqueCount; i++)
    {
        chars[i] = dfArray[i].data;
        freqs[i] = dfArray[i].freq;
    }
    free(dfArray);

    Node **arr = (Node **)malloc(sizeof(Node *) * uniqueCount);
    int count = 0;
    for (int i = 0; i < uniqueCount; i++)
    {
        if (freqs[i] > 0)
        {
            arr[count] = newNode(chars[i], freqs[i]);
            count++;
        }
    }

    heap *h = createHeap(uniqueCount, arr);

    while (h->size > 1)
    {
        Node *left = extractMin(h);
        Node *right = extractMin(h);

        Node *mergedNode = newNode('$', left->freq + right->freq);
        mergedNode->left = left;
        mergedNode->right = right;

        insert(h, mergedNode);
    }

    Node *minNode = extractMin(h);
    return minNode;
}

void generateCodes(Node *root, char *code, int depth, HuffmanCode huffmanTable[256])
{
    if (!root)
        return;

    if (root->left == NULL && root->right == NULL)
    {
        code[depth] = '\0'; // Null terminate the code string
        strcpy(huffmanTable[(unsigned char)root->data].code, code);
        huffmanTable[(unsigned char)root->data].data = root->data;
        return;
    }

    code[depth] = '0';
    generateCodes(root->left, code, depth + 1, huffmanTable);

    code[depth] = '1';
    generateCodes(root->right, code, depth + 1, huffmanTable);
}
