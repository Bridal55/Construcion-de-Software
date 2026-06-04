// Julian berges | A01787490
// C parallel
//gcc -o factorial factorial.c -lpthread -lm


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <pthread.h>


#define MAX_COUNT 10000000


typedef struct {
    int id;
    int start;
    int end;

    // Pointer to the variable where the result will be computed
    unsigned long long * counter_ptr;
    // A pointer to the mutex used by all threads
    pthread_mutex_t * mutex_ptr;

} 

data_t;

// Function declaration
unsigned long long factorial(int n);

unsigned long long num_to_bin(unsigned long long result);
unsigned int one_counter(unsigned long long binary);

void * threadFunction (void * data);


int main(int argc, char * argv[])
{
    int status;
    int n = 5;
    int threads = 1;
    
    
    if (argc == 3) {
        threads = atoi(argv[2]);
    }
    if (argc > 1) {
        n = atoi(argv[1]);
    }

    int rangeSize = n / threads;
    int remainder = n % threads;

    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


    // Create an array of structures
    pthread_t tid[threads];
    data_t thread_data[threads];

    // Variable to store the factorial computed in parallel
    unsigned long long resultParallel = 1;

    printf("Launching threads\n");
    // Loop to call the functions as many times as threads
    for (int i=0; i<threads; i++) {
        thread_data[i].id = i;
        thread_data[i].start = i * rangeSize + 1;
        thread_data[i].end = (i + 1) * rangeSize;
        thread_data[i].counter_ptr = &resultParallel;
        thread_data[i].mutex_ptr = &mutex;

    if (i == threads - 1)
                thread_data[i].end += remainder;

        int status = pthread_create(&tid[i], NULL, threadFunction, &thread_data[i]);
        printf("Created thread: %d  [%d, %d]\n", i, thread_data[i].start, thread_data[i].end);
        if (status == -1)
            perror("ERROR: pthread_create");
    }

        printf("Going to pthread_join\n");

        for (int i = 0; i < threads; i++) {
            int status = pthread_join(tid[i], NULL);
            if (status == -1)
                perror("ERROR: pthread_join");
        }

        unsigned long long binary = num_to_bin(resultParallel);
        printf("Number of 1's in binary of  %d! = %u\n", n, one_counter(resultParallel));
        pthread_exit(NULL);
    }





    void *threadFunction(void *data) {
        data_t *info = (data_t *)data;
        printf("\tRunning thread %d\n ", info->id);

        
        unsigned long long local_product = 1;
        for (int i = info->start; i <= info->end && i <= MAX_COUNT; i++)
            local_product *= i;

        pthread_mutex_lock(info->mutex_ptr);
        (*info->counter_ptr) *= local_product;
        pthread_mutex_unlock(info->mutex_ptr);

        

        pthread_exit(NULL);
    }


// Function to compute the factorial of a number n
unsigned long long factorial(int n)
{
    unsigned long long result = 1;

    for (int i=1; i<=n; i++) {
        result *= i;
    }

    return result;
}


unsigned long long num_to_bin(unsigned long long result){
    unsigned long long binary = 0;
    unsigned long long base = 1;

    while (result > 0) {
        int digit = result % 2;
        binary += digit * base;
        base *= 10;
        result /= 2;
    }

    return binary;
}

unsigned int one_counter(unsigned long long number) {
    unsigned int count = 0;

    while (number > 0) {
        if (number % 2 == 1) {
            count++;
        }
        number /= 2;
    }

    return count;
}
