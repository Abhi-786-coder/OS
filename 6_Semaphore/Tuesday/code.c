#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>


#define MAX_CONN 3

sem_t semaphore;

void* handle_client(void* arg)
{
	int client_id = *(int*)arg;

	// acquire semaphore
	sem_wait(&semaphore);

	printf("Client %d connected\n", client_id);

	//simualte work
	sleep(2);

	printf("Client %d disconnected\n", client_id);

	// release semaphore
	sem_post(&semaphore);


	free(arg);
	return NULL;
}


int main()
{
	pthread_t threads[10];

	//Initialise semaphore with MAX_CONN

	sem_init(&semaphore,0,MAX_CONN);

	for(int i=0;i<10;i++)
	{
		int* client_id = malloc(sizeof(int));
		*client_id = i+1;
		pthread_create(&threads[i],NULL,handle_client,client_id);
	}

	for(int i=0;i<10;i++)
	{
		pthread_join(threads[i], NULL);
	}


	sem_destroy(&semaphore);
	return 0;
}