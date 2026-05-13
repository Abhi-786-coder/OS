#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdatomic.h>

#define TOTAL_TRANSACTIONS 1000000

int N; // number of threads

// Shared counters (atomic)
atomic_long total_processed = 0;
atomic_long total_success = 0;

// Thread function
void* process_transactions(void* arg)
{
    int id = *(int*)arg;
    free(arg);

    int per_thread = TOTAL_TRANSACTIONS / N;

    for (int i = 0; i < per_thread; i++)
    {
        int valid = rand() % 2;  // random success/failure

        if (valid)
        {
            atomic_fetch_add(&total_success, 1);
        }

        atomic_fetch_add(&total_processed, 1);
    }

    return NULL;
}


int main()
{
    printf("Enter number of threads: ");
    scanf("%d", &N);

    pthread_t threads[N];

    clock_t start = clock();

    // Create threads
    for (int i = 0; i < N; i++)
    {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&threads[i], NULL, process_transactions, id);
    }

    // Join threads
    for (int i = 0; i < N; i++)
    {
        pthread_join(threads[i], NULL);
    }

    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nTotal Processed = %ld\n", total_processed);
    printf("Successful Transactions = %ld\n", total_success);
    printf("Execution Time = %f seconds\n", time_taken);

    return 0;
}