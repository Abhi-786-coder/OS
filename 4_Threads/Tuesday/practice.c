#include<stdio.h>
#include<stdlib>
#include<pthread.h>
#include<time.h>


#define total_elements 10000000

int number_of_threads;

int *arr;
int *partial_sum;


void* function(void* args)
{
    int* id = *(int*)args;
    free(args);

    int start = id*(total_elements/number_of_threads);
    int end = (id+1)*(total_elements/number_of_threads);

    int sum = 0;
    for(int i =start;i<end;i++)
    {
        sum += arr[i];
    }

    partial_sum[id] = sum;
    return NULL;
}

int main()
{
    printf("Enter number of threads: ");
    scanf("%d",&number_of_threads);


    pthread_t threads[number_of_threads];

    arr = (double*)malloc(N*sizeof(double*));

    partial_sum = (double*)malloc(T*sizeof(double*));


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

    double total =0;
    for(auto i : partial_sum)
    {
        total += i;
    }
}