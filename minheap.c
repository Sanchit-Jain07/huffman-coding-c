#include "funcs.h"

heap *createHeap(int capacity, Node **arr)
{
    heap *h = (heap *)malloc(sizeof(heap));

    if (h == NULL)
    {
        printf("Memory Error");
        return NULL;
    }

    h->size = 0;
    h->capacity = capacity;

    h->arr = (Node **)malloc(capacity * sizeof(Node *));

    if (h->arr == NULL)
    {
        printf("Memory Error");
        return NULL;
    }
    int i;
    for (i = 0; i < capacity; i++)
    {
        h->arr[i] = arr[i];
    }

    h->size = i;
    i = (h->size - 2) / 2;
    while (i >= 0)
    {
        heapify(h, i);
        i--;
    }
    return h;
}

void heapify(heap *h, int index)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < 0 || left >= h->size)
    {
        left = -1;
    }

    if (right < 0 || right >= h->size)
    {
        right = -1;
    }

    if (left != -1 && (h->arr[left]->freq < h->arr[smallest]->freq))
    {
        smallest = left;
    }

    if (right != -1 && (h->arr[right]->freq < h->arr[smallest]->freq))
    {
        smallest = right;
    }

    if (smallest != index)
    {
        Node *temp = h->arr[smallest];
        h->arr[smallest] = h->arr[index];
        h->arr[index] = temp;

        heapify(h, smallest);
    }
}

void heapifyUp(heap *h, int index)
{
    int parent = (index - 1) / 2;

    if (index > 0 && h->arr[index]->freq < h->arr[parent]->freq)
    {
        Node *temp = h->arr[parent];
        h->arr[parent] = h->arr[index];
        h->arr[index] = temp;

        heapifyUp(h, parent);
    }
}

void insert(heap *h, Node *node)
{
    if (h->size == h->capacity)
    {
        printf("Heap Overflow");
        return;
    }

    h->arr[h->size] = node;
    heapifyUp(h, h->size);
    h->size++;
}

Node *extractMin(heap *h)
{
    if (h->size <= 0)
    {
        printf("Heap is empty!\n");
        return NULL;
    }
    Node *min = h->arr[0];
    h->arr[0] = h->arr[h->size - 1];
    h->size--;
    heapify(h, 0);
    return min;
}

void printHeap(heap *h)
{

    for (int i = 0; i < h->size; i++)
    {
        printf("%d ", h->arr[i]);
    }
    printf("\n");
}
