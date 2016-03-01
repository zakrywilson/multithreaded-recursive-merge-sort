/*
 * Zach Wilson
 * Multithreading Merge Sort
 * mergesort.cpp
 */


#include <iostream>
#include <pthread.h>
#include <time.h>
#include "mergesort.h"


void *merge_sort(void* p);
void merge(int *numbers, int size, int low, int mid, int high);
void load(struct SortArgs *p, int *_numbers, int _size, int _low, int _high);


/* Holds array data to be passed into pthread_create */
struct SortArgs {
  int *numbers;
  int size;
  int low;
  int high;
};

/* Loads the parameters into the structure */
void load(struct SortArgs *p, int *_numbers, int _size, int _low, int _high) {
  p->numbers = _numbers;
  p->size = _size;
  p->low = _low;
  p->high = _high;
}

/* Recursive merging and sorting */
void *merge_sort(void* p) {

  struct SortArgs *args = (struct SortArgs *) p;
  int mid;
  struct SortArgs left, right;

  if (args->low < args->high) {
    mid = (args->low + args->high) / 2;

    load(&left, args->numbers, args->size, args->low, mid);
    merge_sort((void *) &left);

    load(&right, args->numbers, args->size, mid + 1, args->high);
    merge_sort((void *) &right);

    merge(args->numbers, args->size, args->low, mid, args->high);
  }

  return NULL;
}

/* Merges arrays together */
void merge(int *numbers, int size, int low, int mid, int high) {

  int temp[size];
  int h, i, j, k;
  h = low;
  i = low;
  j = mid + 1;

  // traverse both parts of the array...
  while ((h <= mid) && (j <= high)) { 

    // if an element of left half of the array is 
    // less than element of right half of the array...
    if (numbers[h] <= numbers[j]) {

      // store left-half element in the temp array
      temp[i] = numbers[h]; 

      // now shift the index of the array 
      // from which the element was copied to temp 
      h++;
    }

    // else, store the right half element in the temp array
    else {

      temp[i] = numbers[j];

      // now shift the index of the array from 
      // which the element was copied to temp 
      j++; 
    }
    i++;
  }

  // if we're done traversing the left half,
  // copy remaining elements from right half to temp
  if (h > mid) {
    for (k = j; k <= high; k++) {
      temp[i] = numbers[k];
      i++;
    }
  }

  // else, copy remaining elements from left half to temp
  else {
    for (k = h; k <= mid; k++) {
      temp[i] = numbers[k];
      i++;
    }
  }

  // recopy the values from temp to original array.
  for (k = low; k <= high; k++) 
    numbers[k] = temp[k];
}

/* Initial merging and sorting */
void merge_sort_start(int *numbers, int size, int low, int high) {

  int mid = (low + high) / 2;
  struct SortArgs left, right;

  pthread_t thread_left, thread_right;

  load(&left, numbers, size, low, mid);
  load(&right, numbers, size, mid + 1, high);

  pthread_create(&thread_left, NULL, &merge_sort, (void *) &left);
  pthread_create(&thread_right, NULL, &merge_sort, (void *) &right);

  pthread_join(thread_left, NULL);
  pthread_join(thread_right, NULL);

  merge(numbers, size, low, mid, high);
}

