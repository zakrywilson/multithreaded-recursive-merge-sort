/*
 * Zach Wilson
 * Benchmark Merge Sort
 *
 * Recursive merge sort that does not
 * implement multithreading to be the
 * benchmark for mergesort.cpp that
 * implements multithreading.
 */


#include <iostream>
#include <time.h>

// sort a million numbers
const int ARRAY_SIZE = 100000;

void merge(int *, int *, int, int, int);

void merge_sort(int *numbers, int *temp, int low, int high) {
  int mid;
  if (low < high) {
    mid = (low + high) / 2;
    merge_sort(numbers, temp, low, mid);
    merge_sort(numbers, temp, mid + 1, high);
    merge(numbers, temp, low, mid, high);
  }
}

void merge(int *numbers, int *temp, int low, int mid, int high) {
  int h, i, j, k;
  h = low;
  i = low;
  j = mid + 1;

  // Traverse both halves of the array
  while ((h <= mid) && (j <= high)) { 

    // if an element of left half is 
    // less than element of right half
    if (numbers[h] <= numbers[j]) {

      // store element of left half in the temporary array
      temp[i] = numbers[h]; 

      // shift the index of the array 
      // from which the element was copied to temporary 
      h++;
    }

    // otherwise store the element of the right half 
    // in the temporary array
    else {

      temp[i] = numbers[j];

      // shift the index of the array from 
      // which the element was copied to temporary 
      j++; 
    }
    i++;
  }

  // if traversal of left half is done, 
  // copy remaining elements from right half to temporary
  if (h > mid) {
    for (k = j; k <= high; k++) {
      temp[i] = numbers[k];
      i++;
    }
  }

  // otherwise copy remaining elements from left half to temporary
  else {
    for (k = h; k <= mid; k++) {
      temp[i] = numbers[k];
      i++;
    }
  }

  // recopy the values from temporary to original array.
  for (k = low; k <= high; k++) 
    numbers[k] = temp[k];
}

int main() {

  int size = ARRAY_SIZE; // size of array
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
}
