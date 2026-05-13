#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_NORTH 5
#define NUM_SOUTH 5

// Semaphores
sem_t bridge; // controls access to the bridge (only one direction at a time)
sem_t mutex;  // protects counters

int north_count = 0;
int south_count = 0;

void *northbound(void *arg)
{
    int id = *(int *)arg;

    sem_wait(&mutex);
    north_count++;
    if (north_count == 1)
    {
        // first northbound farmer locks the bridge
        sem_wait(&bridge);
    }
    sem_post(&mutex);

    printf("Northbound farmer %d is crossing the bridge\n", id);
    sleep(1);
    printf("Northbound farmer %d has crossed\n", id);

    sem_wait(&mutex);
    north_count--;
    if (north_count == 0)
    {
        // last northbound farmer releases the bridge
        sem_post(&bridge);
    }
    sem_post(&mutex);

    free(arg);
    return NULL;
}

void *southbound(void *arg)
{
    int id = *(int *)arg;

    sem_wait(&mutex);
    south_count++;
    if (south_count == 1)
    {
        // first southbound farmer locks the bridge
        sem_wait(&bridge);
    }
    sem_post(&mutex);

    printf("Southbound farmer %d is crossing the bridge\n", id);
    sleep(1);
    printf("Southbound farmer %d has crossed\n", id);

    sem_wait(&mutex);
    south_count--;
    if (south_count == 0)
    {
        // last southbound farmer releases the bridge
        sem_post(&bridge);
    }
    sem_post(&mutex);

    free(arg);
    return NULL;
}

int main()
{
    pthread_t north_threads[NUM_NORTH];
    pthread_t south_threads[NUM_SOUTH];

    // Initialize semaphores
    sem_init(&bridge, 0, 1); // only one direction at a time
    sem_init(&mutex, 0, 1);  // mutual exclusion for counters

    // Create northbound farmers
    for (int i = 0; i < NUM_NORTH; i++)
    {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&north_threads[i], NULL, northbound, id);
    }

    // Create southbound farmers
    for (int i = 0; i < NUM_SOUTH; i++)
    {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&south_threads[i], NULL, southbound, id);
    }

    // Wait for all farmers
    for (int i = 0; i < NUM_NORTH; i++)
    {
        pthread_join(north_threads[i], NULL);
    }
    for (int i = 0; i < NUM_SOUTH; i++)
    {
        pthread_join(south_threads[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&bridge);
    sem_destroy(&mutex);

    return 0;
}
