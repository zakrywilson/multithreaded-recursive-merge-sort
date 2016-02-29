/*
 * Zach Wilson
 * Benchmark Merge Sort
 * benchmark.h
 */

#ifndef BENCHMARK_H
#define BENCHMARK_H

class MergeSort {

 public:

 	MergeSort();

  ~MergeSort();

  void merge_sort(int *, int *, int, int);

  void merge(int *, int *, int, int, int);

};

#endif