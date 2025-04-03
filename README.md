# Huffman Compression in C

A simple file compression and decompression program using Huffman coding, implemented in C.

## Features

-   Compresses text files using Huffman encoding
-   Decompresses files back to their original form
-   Efficiently builds Huffman trees based on character frequencies
-   Implements priority queue (min-heap) for optimal Huffman tree construction

## How It Works

1. **Compression**

    - Reads the input file and counts character frequencies.
    - Builds a Huffman tree and generates binary codes for each character.
    - Encodes the file using these codes and writes the compressed data.

2. **Decompression**
    - Reads the Huffman tree from the compressed file.
    - Decodes the binary data back to the original text.

## Installation & Compilation

Make sure you have `gcc` installed. Then, compile the project using:

```sh
gcc -o compressor minheap.c huffman.c compress.c
gcc -o decompressor minheap.c huffman.c decompress.c
```

## Usage

### Compress a file

```sh
./compressor input.txt [compressed.bin]
```

### Decompress a file

```sh
./decompressor compressed.bin output.txt
```

## File Format

-   The compressed file stores character frequencies and encoded binary data.
-   The decompression process reconstructs the Huffman tree from the file header.

## Learning Outcomes

This project helped in understanding:

-   Huffman coding algorithm
-   Memory management, pointers and bitwise operations in C
-   File handling in C
-   Min-heaps and priority queues

## Future Improvements

-   Add support for compressing images and binary files
-   Optimize memory usage
-   Implement a GUI or CLI options for better usability
