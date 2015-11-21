/*
 * Zach Wilson
 * Multithreading Merge Sort
 */


#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <pthread.h>


// sort a million numbers
const int ARRAY_SIZE = 100000;

// Holds array data to be passed into pthread_create
struct sort_args {
  int *numbers;
  int size;
  int low;
  int high;
};

// loads the params into structure
inline void loader(struct sort_args *p, int *n, int s, int l, int h) {
  p->numbers = n;
  p->size = s;
  p->low = l;
  p->high = h;
}

void merge(int *, int, int, int, int);

void* merge_sort(void* p);

// Initial merging and sorting called only by main
void merge_sort_start(int *numbers, int size, int low, int high) {

  int mid = (low + high) / 2;
  struct sort_args left, right;

  pthread_t thread_left, thread_right;

  loader(&left, numbers, size, low, mid);
  loader(&right, numbers, size, mid + 1, high);

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
  struct sort_args left, right;

  if (args->low < args->high) {
    mid = (args->low + args->high) / 2;

    loader(&left, args->numbers, args->size, args->low, mid);
    merge_sort((void *) &left);

    loader(&right, args->numbers, args->size, mid + 1, args->high);
    merge_sort((void *) &right);

    merge(args->numbers, args->size, args->low, mid, args->high);
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

  int size = ARRAY_SIZE; // size of array
  int numbers[size]; // array to sort
  int temp[size]; // temp array for merging

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
  merge_sort_start(numbers, size, 0, size - 1);

  // print the sorted array
  std::cout << std:: endl << "sorted:   ";
  for (int i = 0; i < size; i++)
    std::cout << numbers[i] << " ";

  std::cout << std::endl;
}
