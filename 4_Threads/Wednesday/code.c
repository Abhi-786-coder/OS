#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

#define N 50000000   // range: 1 to N

int T; // number of threads
int *partial_count;

// Function to check prime
int is_prime(int num)
{
    if (num < 2)
    {
        return 0;
    }

    for (int i = 2; i <= sqrt(num); i++)
    {
        if (num % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

// Thread function
void* count_primes(void* arg)
{
    int id = *(int*)arg;
    free(arg);

    int start = id * (N / T) + 1;
    int end = (id + 1) * (N / T);

    int count = 0;

    for (int i = start; i <= end; i++)
    {
        if (is_prime(i))
        {
            count++;
        }
    }

    partial_count[id] = count;

    return NULL;
}

int main()
{
    printf("Enter number of threads: ");
    scanf("%d", &T);

    pthread_t threads[T];
    partial_count = (int*)malloc(T * sizeof(int));

    // Start timer
    clock_t start_time = clock();

    // Create threads
    for (int i = 0; i < T; i++)
    {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&threads[i], NULL, count_primes, id);
    }

    // Join threads
    for (int i = 0; i < T; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Aggregate results
    int total_primes = 0;
    for (int i = 0; i < T; i++)
    {
        total_primes += partial_count[i];
    }

    // End timer
    clock_t end_time = clock();
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("\nTotal Prime Numbers = %d\n", total_primes);
    printf("Execution Time = %f seconds\n", time_taken);

    free(partial_count);

    return 0;
}