/*
 * Zach Wilson
 * Benchmark Merge Sort
 * main.cpp
 *
 * Recursive merge sort that does not implement multithreading to be the
 * benchmark for mergesort.cpp that implements multithreading.
 */


#include <iostream>
#include <time.h>
#include "benchmark.h" 


int main() {

  int size = 100000; // size of array
  int numbers[size]; // array to sort
  int temp[size]; // temp array for merging
  clock_t start, end; // used for timing

  // seed random number generator
  srand(time(NULL));

  // load up array to sort and print values
  std::cout << "unsorted: ";
  for (int i, number = 0; i < size; i++) {
    number = (rand() % 10000) - 5000;
    numbers[i] = number;
    std::cout << number << " ";
  }

  // sort the thing
  start = clock();
  merge_sort(numbers, temp, 0, size - 1);
  end = clock();

  // print the sorted array
  std::cout << std:: endl << "sorted:   ";
  for (int i = 0; i < size; i++)
    std::cout << numbers[i] << " ";

  std::cout << std::endl;
  float per_ms = (CLOCKS_PER_SEC/1000);
  float run_time = ((float)end - (float)start) / per_ms;
  std::cout << run_time << " ms" << std::endl;

  return 0;
} 
