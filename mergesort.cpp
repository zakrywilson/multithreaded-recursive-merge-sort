/*
 * Zach Wilson
 */

#include <iostream>

void merge(int *, int *, int, int, int);

void merge_sort(int *numbers, int *temp, int low, int high) {
  int mid;
  if (low < high) {
    mid = (low + high)/2;
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
  int numbers[] = {12, 10, 43, 23, -78, 45, 123, 56, 98, 41, 90, 24};
  int num;

  num = sizeof(numbers)/sizeof(int);

  // temporary array to be used for merging
  int temp[num]; 

  merge_sort(numbers, temp, 0, num - 1);

  for (int i = 0; i < num; i++)
    std::cout << numbers[i] << " ";

  std::cout << std::endl;
}
