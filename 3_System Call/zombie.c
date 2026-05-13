#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    pid = fork();

    if(pid == 0)
    {
        // Child process
        printf("Child process (PID: %d) exiting immediately\n", getpid());
        exit(0);   // finishes FAST → becomes zombie
    }
    else
    {
        // Parent process
        printf("Parent process (PID: %d)\n", getpid());
        printf("Child PID: %d\n", pid);

        printf("Parent sleeping for 15 seconds...\n");
        printf("👉 Run 'ps -l' in another terminal NOW!\n");

        sleep(15);  // keeps parent alive → zombie visible

        printf("Parent exiting (zombie will be cleaned now)\n");
    }

    return 0;
}