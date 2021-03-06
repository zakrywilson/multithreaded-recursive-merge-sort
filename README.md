# Multithreaded Recursive Merge Sort

Recursive merge sort with POSIX threads

## How to run

### Mergesort

Run with script  
`> ./run`

Run manually  
`> clang++ -lpthread main.cpp mergesort.cpp -o mergesort.out`  
`> ./mergesort.out`  

### Benchmark

Run with script  
`> ./run`

Run manually  
`> clang++ main.cpp benchmark.cpp -o benchmark.out`  
`> ./benchmark.out`  

## Requirements

* C++ 98 (or later)
* POSIX threads
* *compiled using clang*
