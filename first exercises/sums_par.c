#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define MAX_NO_OF_THREADS 2
#define MAX_NO_OF_ELEMENTS 100000000

typedef struct arg_data {
    int start;
    int end;
} arg_data;

//array which will be summed
static int* arr;

//sum variable that will store the total sum
static long long int sum = 0;

//Mutex for sum
pthread_mutex_t sum_mutex = PTHREAD_MUTEX_INITIALIZER;

void* worker_sum(void* arg) {
    arg_data* current_thread_data = (arg_data*)arg;
    long long int current_thread_sum = 0;

    //Generate the sum
    for(int i = current_thread_data->start; i < current_thread_data->end; i++)
        current_thread_sum += arr[i];

    //Lock and update sum
    pthread_mutex_lock(&sum_mutex);
    sum += current_thread_sum;
    pthread_mutex_unlock(&sum_mutex);

    return NULL;
}

int main() {
    //Allocate memory for the array
    arr = (int*) malloc(sizeof(int) * MAX_NO_OF_ELEMENTS);
    if (arr == NULL) {
        printf("malloc failed!\n");
        return -1;
    }

    //Let the array consists of first MAX_NO_OF_ELEMENTS integers,
    // 1 to MAX_NO_OF_ELEMENTS
    for (int i = 0; i < MAX_NO_OF_ELEMENTS; i++)
        arr[i] = i + 1;

    //Pthread objects
    pthread_t id[MAX_NO_OF_THREADS];

    //Argument data to send in worker functions
    arg_data arg_arr[MAX_NO_OF_THREADS];

    //Setup timing
    clock_t start, end;
    double cpu_time_taken;
    start = clock();

    //Creating the child threads
    for(int i = 0; i < MAX_NO_OF_THREADS; i++) {
        arg_arr[i].start = i * (MAX_NO_OF_ELEMENTS / MAX_NO_OF_THREADS);
        arg_arr[i].end = (i + 1) * (MAX_NO_OF_ELEMENTS / MAX_NO_OF_THREADS);
        pthread_create(&id[i], NULL, worker_sum, &arg_arr[i]);
    }

    //Joining the threads one by one
    for(int i = 0; i < MAX_NO_OF_THREADS; i++) {
        pthread_join(id[i], NULL);
    }

    end = clock();
    cpu_time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("All child threads have finished their works...\n");
    printf("Total sum: %lld\n", sum);
    printf("Time taken to sum all the numbers is %lf\n", cpu_time_taken);

    //Free allocated memory
    free(arr);

    return 0;
}
