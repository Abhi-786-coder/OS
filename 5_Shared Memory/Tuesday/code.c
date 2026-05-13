#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE 4

struct shared_data
{
	int arr[SIZE];
	int sum;
	float avg;
};


int main()
{
	// you must have a file names shmfile in the directory 
	key_t key = ftok("shmfile", 65);

	int shmid = shmget(key, sizeof(struct shared_data), 0666 | IPC_CREAT);

    struct shared_data *data = (struct shared_data*) shmat(shmid, NULL, 0);

    printf("Parent storing numbers: \n");
    for(int i=0; i<SIZE; i++)
    {
    	data->arr[i] = (i + 1) * 10;
    	prinf("%d", data->arr[i]);
    }


    data->sum = 0;
    for(int i=0;i<SIZE;i++)
    {
    	data->sum += data->arr[i];
    }

	printf("\nParent computed sum = %d\n", data->sum);

	pid_t pid = fork();

	if(pid==0)
	{
		printf("Child is reading sum = %d\n", data->sum);

		data->avg = (float)data->sum / SIZE;

		printf("Child computed average = %.2f\n", data->avg);

		shmdt(data);
		exit(0);
	}
	else
	{
		wait(NULL);

		printf("\n Parent is reading average: %.2f\n", data->avg);

		shmdt(data);
		shmctl(shmid,IPC_RMID,NULL);
	}

	return 0;

}