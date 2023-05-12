#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "sorting_algorithms.c"

//1st file with 100000 (I)
//2nd file with 1000000 (II)
//3rd file with 10000000 (III)
//4th file with 50000000 (IV)
//5th file with 500000000 (V)
//6th file with 1~2 bil (VI) 2000000000


//0_1 file with 25000
//0_2 file with 50000



int main() {
    int size = 10000000, partitions = 10;
    int subarray_size = size / partitions; // size of each sub-array

    FILE *file = fopen("C:/faculta/.C programming/MPI 1st activity PROJECT/DATA SETS/DATA_SET_3.bin", "rb");
    if (!file) {
        printf("Failed to open file\n");
        return 1;
    }

    int* values = (int*) malloc(size * sizeof(int));
    if (!values) {
        printf("Failed to allocate memory\n");
        return 1;
    }



    struct timespec start1, end1;
    clock_gettime(CLOCK_REALTIME, &start1);

    size_t elements_read = fread(values, sizeof(int), size, file);

    int **subarrays = (int **) malloc(partitions * sizeof(int *)); // allocate memory for the array of sub-arrays
    if (partitions>1) {
        for (int i = 0; i < partitions; i++) {
            subarrays[i] = (int *) malloc(subarray_size * sizeof(int));
            for (int j = 0; j < subarray_size; j++) {
                subarrays[i][j] = values[i * subarray_size + j];
            }
        }
        free(values);
    }

    clock_gettime(CLOCK_REALTIME, &end1);
    double start_time1 = (double) start1.tv_sec + (double) start1.tv_nsec / 1e9;
    double end_time1 = (double) end1.tv_sec + (double) end1.tv_nsec / 1e9;
    double time_taken1 = end_time1 - start_time1;

    if (elements_read != size) {
        printf("Failed to read all elements from file\n");
        return 1;
    }

    fclose(file);

    for (int i = 0; i < 10; i++) {
        printf("%d ", values[i]);
    }
    printf("\n");

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    if (partitions > 1){
        for (int i = 0; i < partitions; i++){
            insertionSort(subarrays[i], subarray_size);
            //bubbleSort(subarrays[i], subarray_size);
            //mergeSort(subarrays[i], 0, subarray_size-1);
            //quickSort(subarrays[i], 0, subarray_size-1);
        }

    }else {
        insertionSort(values, size);
        //bubbleSort(values, size);
        //mergeSort(values, size);
        //quickSort(values, 0, size - 1);
    }

    clock_gettime(CLOCK_REALTIME, &end);
    double start_time = (double) start.tv_sec + (double) start.tv_nsec / 1e9;
    double end_time = (double) end.tv_sec + (double) end.tv_nsec / 1e9;
    double time_taken = end_time - start_time;


    // Print the values in the array




    if (partitions == 1) {
        for (int i = 0; i < 10; i++) {
            printf("%d ", values[i]);
        }
        free(values);
    } else if(partitions > 1) {
        for (int i = 0; i < 100; i++) {
            printf("%d ", subarrays[0][i]);
        }
        free(subarrays);
    }

    printf("\n\nTime taken: %f seconds\n", time_taken);
    printf("\nTime taken to partition: %f seconds\n", time_taken1);
    return 0;
}
