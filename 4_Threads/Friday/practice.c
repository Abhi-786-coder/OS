#include<stdio.h>
#include<time.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>


#define TOTAL_TRANSACTIONS 10000000;

#define WITHDRAW_AMOUNT 10;

int number_of_threads;

pthread_mutex_t lock;

long balance = 1000000;


void* withdraw(void* args)
{
	int* id = *(int*)args;
	free(args);

	int per_thread = TOTAL_TRANSACTIONS/number_of_threads;

	for(int i=0;i<per_thread;i++)
	{
		pthread_mutex_lock(&lock);

		if(balance >= WITHDRAW_AMOUNT)
		{
			balance -= WITHDRAW_AMOUNT
		}

		pthread_mutex_unlock(&lock);
	}

	return NULL;
}


int main()
{
	printf("Enter the number of threads: ");
	scanf("%d", &number_of_threads);

	pthread_t threads[number_of_threads];

	clock_t start = clock();

	for(int i=0;i<number_of_threads;i++)
	{
		pthread_create(&threads[i],NULL,withdraw,NULL);
	}


	for(int i=0;i<number_of_threads;i++)
	{
		pthread_join(&threads[i],NULL);
	}

	clock_t end = clock();


	pthread_mutex_destroy(&lock);
	return 0;
}