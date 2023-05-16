#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NO_OF_ELEMENTS 100000000

static long long int sum;
static int *arr;

int main() {
    arr = (int*) malloc(sizeof(int) * MAX_NO_OF_ELEMENTS);
    if (arr == NULL) {
        printf("malloc failed!\n");
        return -1;
    }
    
    //let the array consists of first MAX_NO_OF_ELEMENTS integers,
    //1 to MAX_NO_OF_ELEMENTS

    for (int i = 0; i < MAX_NO_OF_ELEMENTS; i++)
        arr[i] = i + 1;

    //Setup timing
    clock_t start, end;
    double cpu_time_taken;

    start = clock();

    //Summing code here

    for (int i = 0; i < MAX_NO_OF_ELEMENTS; i++)
        sum += arr[i];

    end = clock();
    
    //Time calculations here
    cpu_time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Total sum: %lld\n", sum);
    printf("Time taken to sum all the numbers are %f seconds.\n", cpu_time_taken);

    free(arr);

    return 0;
}