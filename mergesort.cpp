/*
 * Zach Wilson
 * Multithreading Merge Sort
 */


#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <pthread.h>

#define STRUCT_LOADER( x, n, s, l, h ) x.numbers = n, x.size = s, x.low = l, x.high = h
#define STRUCT_LOADER_POINTER( x, n, s, l, h ) x->numbers = n, x->size = s, x->low = l, x->high = h


void merge(int *, int, int, int, int);

void* merge_sort(void* p);

// Holds array data to be passed into pthread_create
struct sort_args {
  int *numbers;
  int size;
  int low;
  int high;
};

// Initial merging and sorting called only by main
void merge_sort_start(int *numbers, int size, int low, int high) {

  int mid = (low + high) / 2;
  struct sort_args left, right;

  pthread_t thread_left, thread_right;

  STRUCT_LOADER(left, numbers, size, low, mid);
  STRUCT_LOADER(right, numbers, size, mid + 1, high);

  pthread_create(&thread_left, NULL, &merge_sort, (void *) &left);
  pthread_create(&thread_right, NULL, &merge_sort, (void *) &right);

  pthread_join(thread_left, NULL);
  pthread_join(thread_right, NULL);

  merge(numbers, size, low, mid, high);
}

// Recursive merging and sorting
void* merge_sort(void* p) {

  struct sort_args *args = (struct sort_args *) p;
  int mid;
  int low_save = args->low;
  int high_save = args->high;

  if (args->low < args->high) {
    mid = (args->low + args->high) / 2;

    STRUCT_LOADER_POINTER(args, args->numbers, args->size, args->low, mid);
    merge_sort((void *) args);

    STRUCT_LOADER_POINTER(args, args->numbers, args->size, mid + 1, high_save);
    merge_sort((void *) args);

    merge(args->numbers, args->size, low_save, mid, high_save);
  }

  return NULL;
}

// Function that merges the arrays together
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

int main() {

  int numbers[] = {55, 12, -100, 10, 43, 23, -78, 45, 123, 56, 98, 41, 90, 24};
  int num;

  num = sizeof(numbers) / sizeof(int);

  std::cout << "Unsorted: ";
  for (int i = 0; i < num; i++)
    std::cout << numbers[i] << " ";

  // temporary array to be used for merging
  int temp[num]; 

  merge_sort_start(numbers, num, 0, num - 1);

  std::cout << std:: endl << "Sorted:   ";
  for (int i = 0; i < num; i++)
    std::cout << numbers[i] << " ";

  std::cout << std::endl;
}
