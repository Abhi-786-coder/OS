#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define TOTAL_TRANSACTIONS 1000000
#define WITHDRAW_AMOUNT 10

int N; // number of threads

long balance = 10000000;  // initial balance

pthread_mutex_t lock;

// Thread function
void* withdraw(void* arg)
{
    int id = *(int*)arg;
    free(arg);

    int per_thread = TOTAL_TRANSACTIONS / N;

    for (int i = 0; i < per_thread; i++)
    {
        pthread_mutex_lock(&lock);

        if (balance >= WITHDRAW_AMOUNT)
        {
            balance -= WITHDRAW_AMOUNT;
        }

        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

int main()
{
    printf("Enter number of threads: ");
    scanf("%d", &N);

    pthread_t threads[N];

    pthread_mutex_init(&lock, NULL);

    clock_t start = clock();

    // Create threads
    for (int i = 0; i < N; i++)
    {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&threads[i], NULL, withdraw, id);
    }

    // Join threads
    for (int i = 0; i < N; i++)
    {
        pthread_join(threads[i], NULL);
    }

    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nFinal Balance = %ld\n", balance);
    printf("Execution Time = %f seconds\n", time_taken);

    pthread_mutex_destroy(&lock);

    return 0;
}