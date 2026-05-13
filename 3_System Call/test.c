#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    printf("Controller Process Started (Parent PID: %d)\n", getpid());

    pid = fork();  // Step 1: create child

    if(pid < 0)
    {
        printf("Fork failed\n");
        exit(1);
    }
        
    else if(pid == 0)
    {
        // Child process
        printf("Child Process Started (PID: %d)\n", getpid());

        // Step 2: execute external utility
        execlp("ls", "ls", "-l", NULL);

        // If exec fails
        printf("Exec failed\n");
        exit(1);
    }

    else
    {
        // Parent process
        int status;

        printf("Parent waiting for child to finish...\n");

        // Step 3: wait for child
        wait(&status);

        // Step 4: check status
        if(WIFEXITED(status))
        {
            printf("Child completed successfully with exit code: %d\n",
                   WEXITSTATUS(status));
        }
        else
        {
            printf("Child did not terminate normally\n");
        }

        printf("Controller Process Finished\n");
    }

    return 0;
}