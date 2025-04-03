#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcs.h"

HuffmanCode huffmanTable[256];

Node *createNode(unsigned char ch, unsigned int freq)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = ch;
    newNode->freq = freq;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node *rebuildTree(FILE *compressedFile)
{
    int numChars;
    unsigned char ch;
    unsigned int freq;

    fread(&numChars, sizeof(int), 1, compressedFile);

    int freqs[256] = {0};
    char chars[256] = {0};

    for (int i = 0; i < numChars; i++)
    {
        fread(&ch, sizeof(unsigned char), 1, compressedFile);
        fread(&freq, sizeof(unsigned int), 1, compressedFile);
        chars[ch] = ch;
        freqs[ch] = freq;
    }
    Node *root = buildTree(chars, freqs, 256, numChars); // Reconstruct Huffman Tree from the frequency table
    return root;
}

void decodeData(FILE *compressedFile, Node *root, FILE *outputFile, int validBitsInLastByte, long fileSize)
{
    Node *current = root;
    unsigned char buffer;
    size_t bitPos;
    int bitCount = 0;
    long bytesRead = ftell(compressedFile);
    while (fread(&buffer, sizeof(unsigned char), 1, compressedFile))
    {
        bytesRead++;
        if (bytesRead == fileSize - sizeof(int))
        {
            bitCount = validBitsInLastByte;
        }
        else if (bytesRead > fileSize - sizeof(int))
        {
            break;
        }
        else
        {
            bitCount = 8;
        }
        for (int i = 7; i >= 8 - bitCount; i--)
        {
            unsigned char bit = (buffer >> i) & 1;
            if (bit == 0)
                current = current->left;
            else
                current = current->right;

            if (current->left == NULL && current->right == NULL)
            {
                fputc(current->data, outputFile);
                current = root;
            }
        }
    }
}

void freeTree(Node *root)
{
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <compressed_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE *compressedFile = fopen(argv[1], "rb");
    if (!compressedFile)
    {
        perror("Unable to open compressed file");
        return 1;
    }

    FILE *outputFile = fopen(argv[2], "wb");
    if (!outputFile)
    {
        perror("Unable to open output file");
        fclose(compressedFile);
        return 1;
    }
    fseek(compressedFile, 0, SEEK_END);
    long fileSize = ftell(compressedFile);
    rewind(compressedFile);

    fseek(compressedFile, fileSize - sizeof(int), SEEK_SET);
    int validBitsInLastByte;
    fread(&validBitsInLastByte, sizeof(int), 1, compressedFile);

    rewind(compressedFile);

    Node *root = rebuildTree(compressedFile);

    decodeData(compressedFile, root, outputFile, validBitsInLastByte, fileSize);

    fclose(compressedFile);

    freeTree(root);

    return 0;
}
