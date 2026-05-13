#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Semaphores
sem_t agent;
sem_t tobacco_smoker;
sem_t paper_smoker;
sem_t match_smoker;

// Agent function
void* agent_func(void* arg)
{
    while (1)
    {
        sem_wait(&agent);

        int r = rand() % 3;

        if (r == 0)
        {
            printf("\nAgent puts Paper + Matches\n");
            sem_post(&tobacco_smoker); // smoker with tobacco acts
        }
        else if (r == 1)
        {
            printf("\nAgent puts Tobacco + Matches\n");
            sem_post(&paper_smoker); // smoker with paper acts
        }
        else
        {
            printf("\nAgent puts Tobacco + Paper\n");
            sem_post(&match_smoker); // smoker with matches acts
        }
    }
}

// Smoker with Tobacco
void* tobacco(void* arg)
{
    while (1)
    {
        sem_wait(&tobacco_smoker);

        printf("Smoker with Tobacco is making cigarette\n");
        sleep(1);
        printf("Smoker with Tobacco finished smoking\n");

        sem_post(&agent);
    }
}

// Smoker with Paper
void* paper(void* arg)
{
    while (1)
    {
        sem_wait(&paper_smoker);

        printf("Smoker with Paper is making cigarette\n");
        sleep(1);
        printf("Smoker with Paper finished smoking\n");

        sem_post(&agent);
    }
}

// Smoker with Matches
void* matches(void* arg)
{
    while (1)
    {
        sem_wait(&match_smoker);

        printf("Smoker with Matches is making cigarette\n");
        sleep(1);
        printf("Smoker with Matches finished smoking\n");

        sem_post(&agent);
    }
}

int main()
{
    pthread_t t_agent, t1, t2, t3;

    // Initialize semaphores
    sem_init(&agent, 0, 1); // agent starts first
    sem_init(&tobacco_smoker, 0, 0);
    sem_init(&paper_smoker, 0, 0);
    sem_init(&match_smoker, 0, 0);

    // Create threads
    pthread_create(&t_agent, NULL, agent_func, NULL);
    pthread_create(&t1, NULL, tobacco, NULL);
    pthread_create(&t2, NULL, paper, NULL);
    pthread_create(&t3, NULL, matches, NULL);

    // Join threads
    pthread_join(t_agent, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    return 0;
}