#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 10000000   // 10 million elements

double *arr;
double *partial_sum;

int T;  // number of threads

// Thread function
void* compute_sum(void* arg)
{
    int id = *(int*)arg;
    free(arg);

    int start = id * (N / T);
    int end = (id + 1) * (N / T);

    double sum = 0;

    for (int i = start; i < end; i++)
    {
        sum += arr[i];
    }

    partial_sum[id] = sum;

    return NULL;
}

int main()
{
    printf("Enter number of threads: ");
    scanf("%d", &T);

    pthread_t threads[T];

    arr = (double*)malloc(N * sizeof(double));
    partial_sum = (double*)malloc(T * sizeof(double));

    // Initialize array with random values
    for (int i = 0; i < N; i++)
    {
        arr[i] = rand() % 100;  // values between 0–99
    }

    // Start timer
    clock_t start_time = clock();

    // Create threads
    for (int i = 0; i < T; i++)
    {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&threads[i], NULL, compute_sum, id);
    }

    // Wait for all threads
    for (int i = 0; i < T; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Aggregate results
    double total = 0;
    for (int i = 0; i < T; i++)
    {
        total += partial_sum[i];
    }

    double average = total / N;

    // End timer
    clock_t end_time = clock();

    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("\nTotal Sum = %.2f\n", total);
    printf("Average = %.2f\n", average);
    printf("Execution Time = %f seconds\n", time_taken);

    // Free memory
    free(arr);
    free(partial_sum);

    return 0;
}