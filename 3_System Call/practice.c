#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
	pid_t pid;

	printf("Controller process started(Parent PID: %d)\n", getpid());

	pid = fork(); // step 1 : create child	

	if(pid<0)
	{
		printf("Child creation failed\n");
		exit(1);
	}
	else if(pid == 0)
	{
		// child process
		printf("Child process started (PID: %d)\n", getpid());

		// execute external utility
		execlp("ls","ls","-l",NULL);

		// if exec fails
		printf("Exec failed \n");
		exit(1);
	}
	else
	{
		// parent process
		int status;
		printf("Parent waiting for the child to finish...\n");
		wait(&status);
		if(WIFEXITED(status))
		{
			printf("Child completed successfully with exit code: %d\n",WIFEXITED(status));
		}
		else
		{
			printf("Child did not complete properly\n");
		}


		printf("Controller process finished\n");

	}

	return 0;

}