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

struct sort_args {
  int *numbers;
  int size;
  int low;
  int high;
};

void merge_sort_start(int *numbers, int size, int low, int high) {

  int mid = (low + high)/2;
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

void merge(int *numbers, int size, int low, int mid, int high) {
  int h, i, j, k;
  h = low;
  i = low;
  j = mid + 1;

  int temp[size];

  // Traverse both halves of the array
  while ((h <= mid) && (j <= high)) { 

    // if an element of left half is 
    // less than element of right half
    if (numbers[h] <= numbers[j]) {

      // store element of left half in the temp array
      temp[i] = numbers[h]; 

      // shift the index of the array 
      // from which the element was copied to temp 
      h++;
    }

    // otherwise store the element of the right half 
    // in the temporary array
    else {

      temp[i] = numbers[j];

      // shift the index of the array from 
      // which the element was copied to temp 
      j++; 
    }
    i++;
  }

  // if traversal of left half is done, 
  // copy remaining elements from right half to temp
  if (h > mid) {
    for (k = j; k <= high; k++) {
      temp[i] = numbers[k];
      i++;
    }
  }

  // otherwise copy remaining elements from left half to temp
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

  int numbers[] = {12, 10, 43, 23, -78, 45, 123, 56, 98, 41, 90, 24};
  int num;

  num = sizeof(numbers) / sizeof(int);

  std::cout << "Unsorted: ";
  for (int i = 0; i < num; i++)
    std::cout << numbers[i] << " ";

  // temporary array to be used for merging
  int temp[num]; 

  merge_sort_start(numbers, num, 0, num - 1);

  std::cout << std:: endl << "Sorted: ";
  for (int i = 0; i < num; i++)
    std::cout << numbers[i] << " ";

  std::cout << std::endl;
}
