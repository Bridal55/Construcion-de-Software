// Julian berges | A01787490
// C parallel
//gcc -o num_integration num_integration.c -lpthread -lm




#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <pthread.h>


typedef struct {
    int id;
    int start;
    int end;
    long long  n;
    // Pointer to the variable where the result will be computed
    double * counter_ptr;
    // A pointer to the mutex used by all threads
    pthread_mutex_t * mutex_ptr; 
} 

data_t;

// Function declaration
void * threadFunction (void * data);
double compute_pi(long n);
double pi_range(long start,long end, long n);



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

    double total = 0;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_t tid[threads];
    data_t thread_data[threads];

    printf("Launching threads\n");

    for (int i = 0; i < threads; i++) {
        thread_data[i].n = n ;
        thread_data[i].id = i;
        thread_data[i].start = i * rangeSize ;
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

    printf("The approximation of pi is %.15f\n", total);
}


    void *threadFunction(void *data)
    {
        data_t *info = (data_t *)data;
        printf("\tRunning thread %d\n", info->id);

        double local_sum = pi_range(info->start, info->end, info->n);
        pthread_mutex_lock(info->mutex_ptr);
        (*info->counter_ptr) += local_sum;
        pthread_mutex_unlock(info->mutex_ptr);

        pthread_exit(NULL);
    }


    double compute_pi(long n) {
        double sum = 0.0;
        double width = 1.0 / n;
        for (long i = 0; i < n; i++) {
        double mid = (i + 0.5) * width;
        double height = 4.0 / (1.0 + mid * mid);
        sum += height;
        }
        return width * sum;
    }

    double pi_range(long start,long end, long n) {
    double sum = 0.0;
    double width = 1.0 / n; 
    for (long i = start; i < end; i++) {
        double mid = (i + 0.5) * width;
        double height = 4.0 / (1.0 + mid * mid);
        sum += height;
        }
    return width * sum; 

    }



// 3.14159265358979323846 pi 