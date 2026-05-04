# Search Algorithm Comparison Program

## Overview
This C++ program reads 1 million 64-bit unsigned integers from a binary file and provides an interactive tool to compare the performance of **Sequential (Linear) Search** versus **Binary Search** algorithms.

## Features
- Loads data efficiently from binary file format
- Implements both sequential and binary search with comparison counting
- Interactive menu-driven interface
- Real-time performance metrics display
- Shows the dramatic difference in comparisons between algorithms

## Compilation

```bash
g++ -std=c++17 -o search_comparison search_comparison.cpp
```

## Running the Program

```bash
./search_comparison
```

## How to Use

1. **Enter a search target** (Menu option 1): Input any unsigned long long integer you want to search for
2. **Perform Sequential Search** (Menu option 2): Executes linear search and displays comparison count
3. **Perform Binary Search** (Menu option 3): Executes binary search and displays comparison count
4. **Quit** (Menu option 4): Exit the program

## Key Features of the Code

### Comparison Counting
Both search functions increment a global `comparisonCount` variable for each comparison made, allowing accurate measurement of algorithm efficiency.

### Sequential Search
- Scans the array from the first element to the last
- Continues until the target is found or the end is reached
- Typically requires O(n) comparisons in the worst case

### Binary Search
- Divides the search space in half with each iteration
- Requires the data to be sorted
- Typically requires O(log n) comparisons in the worst case

## Example Results
When searching for a target not in the array:
- **Sequential Search**: ~2.17 million comparisons (scans entire array)
- **Binary Search**: ~21 comparisons (logarithmic efficiency)

The binary search is approximately **100,000 times faster** for this dataset!

## Program Structure
- `seqSearch()`: Template function implementing sequential search
- `binarySearch()`: Template function implementing binary search
- `displayMenu()`: Renders the interactive menu interface
- `main()`: Loads data and manages the main program loop
