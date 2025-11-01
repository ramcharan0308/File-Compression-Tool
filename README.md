# File Compression Tool

## Project Overview

This project implements a file compression tool utilizing Huffman encoding to efficiently compress and decompress text files. It features a comprehensive implementation in C++, showcasing core data structures like linked lists, binary trees, min-heaps, and hash tables.

## Directory Structure

```
File-Compression-Tool/
├── README.md
├── Makefile
├── .gitignore
├── Header.h              # Data structures and algorithm implementations
├── Source.cpp            # Main program logic
├── input.txt             # Sample input file
├── compressed.txt        # Generated compressed file
└── decompress.txt        # Generated decompressed file
```

## Technologies Used

- **C++**: Core programming language
- **Standard Template Library (STL)**: Utilizes vectors, iterators, and other STL containers
- **File I/O**: For handling input and output operations

## Key Functionalities

- **Compression**: Compresses text files using Huffman encoding.
- **Decompression**: Decompresses the compressed files back to their original content.
- **Hash Tables**: Efficiently manages and retrieves character frequencies and encoding mappings.
- **Huffman Algorithm**: Constructs optimal prefix codes to minimize file size.

## Usage

### Compilation

Compile the program using a C++ compiler (e.g., g++):

```bash
g++ -std=c++11 -Wall -Wextra -O2 -o compression_tool Source.cpp
```

### Execution

Run the compiled executable:

```bash
./compression_tool
```

The program reads from `input.txt`, compresses the content, and writes the compressed data to `compressed.txt`. It then decompresses the data from `compressed.txt` and outputs the result to `decompress.txt`.

## Files Description

- **`Header.h`**: Contains data structures (linked lists, binary trees, min-heaps, hash tables) and Huffman encoding logic.
- **`Source.cpp`**: Implements the main workflow for file compression and decompression.
- **`input.txt`**: Input file containing text to be compressed.
- **`compressed.txt`**: Output file containing compressed binary data.
- **`decompress.txt`**: Output file containing decompressed text matching original content.

## Functional Overview

- Reads the input text file and generates frequency data for each character.
- Constructs a Huffman tree based on character frequencies.
- Generates binary codes for each character using the Huffman tree.
- Compresses the input text into binary format and writes it to `compressed.txt`.
- Decompresses the binary data back into the original text and writes it to `decompress.txt`.

## Algorithm Details

### Huffman Encoding Process
1. **Frequency Calculation**: Count occurrence of each character
2. **Tree Construction**: Build binary tree with characters as leaves
3. **Code Assignment**: Assign shorter codes to more frequent characters
4. **Compression**: Replace characters with their binary codes
5. **Decompression**: Use the same tree to decode binary back to text

### Data Structures Used
- **Hash Tables**: For O(1) character frequency lookup and code retrieval
- **Min-Heap**: For efficient tree construction during Huffman algorithm
- **Binary Tree**: For storing the Huffman tree structure
- **Linked Lists**: For hash table collision handling

## Performance

- **Compression Ratio**: Typically 20-50% reduction in file size for text files
- **Time Complexity**: O(n log n) for tree construction, O(n) for encoding/decoding
- **Space Complexity**: O(k) where k is the number of unique characters

## Testing

The project includes sample text in `input.txt` for testing. After running the program:
- Compare `input.txt` with `decompress.txt` to verify correctness
- Check `compressed.txt` to see the binary representation
