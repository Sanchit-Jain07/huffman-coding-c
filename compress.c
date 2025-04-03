#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

HuffmanCode huffmanTable[256];

void encodeFile(const char *inputFile, const char *outputFile, int freq[256])
{
    FILE *in = fopen(inputFile, "rb");
    FILE *out = fopen(outputFile, "wb");
    if (!in || !out)
    {
        printf("Error opening files!\n");
        return;
    }

    int uniqueCount = 0;
    for (int i = 0; i < 256; i++)
        if (freq[i] > 0)
            uniqueCount++;

    fwrite(&uniqueCount, sizeof(int), 1, out);

    for (int i = 0; i < 256; i++)
        if (freq[i] > 0)
        {
            fwrite(&i, sizeof(char), 1, out);
            fwrite(&freq[i], sizeof(int), 1, out);
        }

    unsigned char buffer = 0;
    int bitCount = 0;
    char ch;
    while (fread(&ch, sizeof(char), 1, in))
    {
        char *code = huffmanTable[(unsigned char)ch].code;

        for (int i = 0; code[i] != '\0'; i++)
        {
            buffer = (buffer << 1) | (code[i] - '0');
            bitCount++;
            if (bitCount == 8)
            {
                fwrite(&buffer, sizeof(char), 1, out);
                buffer = 0;
                bitCount = 0;
            }
        }
    }
    if (bitCount > 0)
    {
        buffer = buffer << (8 - bitCount);
        fwrite(&buffer, sizeof(char), 1, out);
    }
    fwrite(&bitCount, sizeof(int), 1, out);
    fclose(in);
    fclose(out);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <input_file> [output_file]\n", argv[0]);
        return 1;
    }

    char *inputFile = argv[1];
    char *encodedFile = (argc >= 3) ? argv[2] : "compressed.bin";

    FILE *in = fopen(inputFile, "rb");
    if (!in)
    {
        perror("Error opening input file");
        return 1;
    }

    int freq[256] = {0};
    char chars[256] = {0};
    char ch;
    while (fread(&ch, sizeof(char), 1, in))
    {
        if (freq[(unsigned char)ch] == 0)
            chars[(unsigned char)ch] = ch;
        freq[(unsigned char)ch]++;
    }
    fclose(in);

    int uniqueCount = 0;
    for (int i = 0; i < 256; i++)
        if (freq[i] > 0)
            uniqueCount++;

    Node *root = buildTree(chars, freq, 256, uniqueCount);

    char code[32];
    generateCodes(root, code, 0, huffmanTable);

    encodeFile(inputFile, encodedFile, freq);
    printf("File compressed successfully! Encoded file: %s\n", encodedFile);

    return 0;
}
