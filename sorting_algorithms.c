#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void insertionSort(int arr[], int size)
{
    int i, key, j;
    for (i = 1; i < size; i++) {
        key = arr[i];
        j = i - 1;
 
        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}



/*
void bubbleSort(int array[], int size) {

  // loop to access each array element
  for (int step = 0; step < size - 1; ++step) {

    // loop to compare array elements
    for (int i = 0; i < size - step - 1; ++i) {

      // compare two adjacent elements
      // change > to < to sort in descending order
      if (array[i] > array[i + 1]) {

        // swapping occurs if elements
        // are not in the intended order
        int temp = array[i];
        array[i] = array[i + 1];
        array[i + 1] = temp;
      }
    }
  }
}
*/


void bubbleSort(int array[], int size) {

    // loop to access each array element
    for (int step = 0; step < size - 1; ++step) {

        bool swapped = false; // flag variable to indicate whether any swaps occurred

        // loop to compare array elements
        for (int i = 0; i < size - step - 1; ++i) {

            // compare two adjacent elements
            // change > to < to sort in descending order
            if (array[i] > array[i + 1]) {

                // swapping occurs if elements
                // are not in the intended order
                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;

                swapped = true; // set flag to true if a swap occurred
            }
        }

        if (!swapped) { // if no swaps occurred, the array is already sorted
            break;
        }
    }
}



//void merge(int arr[], int l, int m, int r)
//{
//    int i, j, k;
//    int n1 = m - l + 1;
//    int n2 = r - m;
//
//    /* create temp arrays */
//    int *L = (int *)malloc(n1 * sizeof(int));
//    int *R = (int *)malloc(n2 * sizeof(int));
//
//    /* Copy data to temp arrays L[] and R[] */
//    for (i = 0; i < n1; i++)
//        L[i] = arr[l + i];
//    for (j = 0; j < n2; j++)
//        R[j] = arr[m + 1 + j];
//
//    /* Merge the temp arrays back into arr[l..r]*/
//    i = 0; // Initial index of first subarray
//    j = 0; // Initial index of second subarray
//    k = l; // Initial index of merged subarray
//    while (i < n1 && j < n2) {
//        if (L[i] <= R[j]) {
//            arr[k] = L[i];
//            i++;
//        }
//        else {
//            arr[k] = R[j];
//            j++;
//        }
//        k++;
//    }
//
//    /* Copy the remaining elements of L[], if there
//    are any */
//    while (i < n1) {
//        arr[k] = L[i];
//        i++;
//        k++;
//    }
//
//    /* Copy the remaining elements of R[], if there
//    are any */
//    while (j < n2) {
//        arr[k] = R[j];
//        j++;
//        k++;
//    }
//    free(L);
//    free(R);
//}
//
///* l is for left index and r is right index of the
//sub-array of arr to be sorted */
//void mergeSort(int arr[], int l, int r)
//{
//    if (l < r) {
//        // Same as (l+r)/2, but avoids overflow for
//        // large l and h
//        int m = l + (r - l) / 2;
//
//        // Sort first and second halves
//        mergeSort(arr, l, m);
//        mergeSort(arr, m + 1, r);
//
//        merge(arr, l, m, r);
//    }
//}

void merge(int arr[], int left[], int left_size, int right[], int right_size) {
    int i, j, k;
    i = j = k = 0;

    while (i < left_size && j < right_size) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < left_size) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < right_size) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int size) {
    if (size < 2) {
        return;
    }

    int mid = size / 2;
    int* left = (int*) malloc(mid * sizeof(int));
    int* right = (int*) malloc((size - mid) * sizeof(int));

    memcpy(left, arr, mid * sizeof(int));
    memcpy(right, arr + mid, (size - mid) * sizeof(int));

    mergeSort(left, mid);
    mergeSort(right, size - mid);
    merge(arr, left, mid, right, size - mid);

    free(left);
    free(right);
}






// function to swap elements
void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

// function to find the partition position
int partition(int array[], int low, int high) {
  
  // select the rightmost element as pivot
  int pivot = array[high];
  
  // pointer for greater element
  int i = (low - 1);

  // traverse each element of the array
  // compare them with the pivot
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
        
      // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i++;
      
      // swap element at i with element at j
      swap(&array[i], &array[j]);
    }
  }

  // swap the pivot element with the greater element at i
  swap(&array[i + 1], &array[high]);
  
  // return the partition point
  return (i + 1);
}

void quickSort(int array[], int low, int high) {
  if (low < high) {
    
    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on right of pivot
    int pi = partition(array, low, high);
    
    // recursive call on the left of pivot
    quickSort(array, low, pi - 1);
    
    // recursive call on the right of pivot
    quickSort(array, pi + 1, high);
  }
}
