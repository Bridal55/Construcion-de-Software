// Julian berges | A01787490
// C parallel
//gcc -o primes primes.c -lpthread -lm





#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <pthread.h>



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
void * threadFunction (void * data);
bool is_prime(int x);
unsigned long long sum_primes(int start, int end);


int main(int argc, char * argv[]){

    int status;
    int n = 15;
    int threads = 1;

    if (argc == 3) {
        threads = atoi(argv[2]);
    }
    if (argc > 1) {
        n = atoi(argv[1]);
    }

    int rangeSize = n / threads;
    int remainder = n % threads;

    unsigned long long total = 0;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_t tid[threads];
    data_t thread_data[threads];

    printf("Launching threads\n");

    for (int i = 0; i < threads; i++) {
        thread_data[i].id = i;
        thread_data[i].start = i * rangeSize + 1;
        thread_data[i].end = (i + 1) * rangeSize;
        thread_data[i].counter_ptr = &total;
        thread_data[i].mutex_ptr = &mutex;

        // Last thread picks up the remainder
        if (i == threads - 1)
            thread_data[i].end += remainder;

        int status = pthread_create(&tid[i], NULL, threadFunction, &thread_data[i]);
        printf("Created thread: %d\n", i);
        if (status == -1)
            perror("ERROR: pthread_create");
    }

    printf("Going to pthread_join\n");

    for (int i = 0; i < threads; i++) {
        int status = pthread_join(tid[i], NULL);
        if (status == -1)
            perror("ERROR: pthread_join");
    }

    printf("The sum of primes up to %d is %llu\n", n, total);
}


    void *threadFunction(void *data)
    {
        data_t *info = (data_t *)data;
        printf("\tRunning thread %d\n", info->id);

        unsigned long long local_sum = sum_primes(info->start, info->end);
        pthread_mutex_lock(info->mutex_ptr);
        (*info->counter_ptr) += local_sum;
        pthread_mutex_unlock(info->mutex_ptr);

        pthread_exit(NULL);
    }

bool is_prime(int x) {

    if (x < 2) return false;
    if (x == 2) return true;

    int limit = (int)ceil(sqrt((double)x));
    
    for (int i = 2; i <= limit; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

unsigned long long sum_primes(int start, int end ){

    int total = 0;
    for (int x = start; x <= end; x++) {
        if (is_prime(x)) {
            total += x;
        }
    }
    return total;
    
}
