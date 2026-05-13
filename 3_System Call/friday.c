#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid1, pid2;

    // Parent process
    printf("Parent Process ID: %d\n", getpid());

    // -------- Child 1 --------
    pid1 = fork();

    if(pid1 == 0)
    {
        // Child 1 process
        printf("Child-1 (before exec) PID: %d\n", getpid());

        // Replace process with wc -l sample.txt
        execlp("wc", "wc", "-l", "sample.txt", NULL);

        // If exec fails
        perror("exec failed");
        exit(1);
    }

    // -------- Child 2 --------
    pid2 = fork();

    if(pid2 == 0)
    {
        // Child 2 process
        printf("Child-2 PID: %d, PPID: %d\n", getpid(), getppid());

        sleep(15);  // sleep for 15 seconds

        printf("Child-2 (after sleep) PID: %d, PPID: %d\n", getpid(), getppid());

        exit(0);
    }

    // -------- Parent Process --------

    // Wait ONLY for Child-1
    waitpid(pid1, NULL, 0);
    printf("Parent collected Child-1\n");

    // Parent exits early
    printf("Parent exiting...\n");

    exit(0);
}