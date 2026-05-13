#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    pid_t pid1, pid2;

    // Parent process
    printf("Parent PID: %d\n", getpid());

    // -------- Child 1 --------
    pid1 = fork();

    if(pid1 == 0)
    {
        // Child-1
        printf("Child-1 PID (before exec): %d\n", getpid());

        // Replace with pwd command
        execlp("pwd", "pwd", NULL);

        // If exec fails
        perror("exec failed");
        exit(1);
    }

    // -------- Child 2 --------
    pid2 = fork();

    if(pid2 == 0)
    {
        // Child-2
        printf("Child-2 PID: %d, PPID: %d\n", getpid(), getppid());

        sleep(12);

        // Append to file
        int fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
        if(fd >= 0)
        {
            char msg[] = "Background task completed\n";
            write(fd, msg, sizeof(msg) - 1);
            close(fd);
        }

        printf("Child-2 finished. PID: %d, New PPID: %d\n", getpid(), getppid());

        exit(0);
    }

    // -------- Parent --------

    // Wait ONLY for Child-1
    waitpid(pid1, NULL, 0);
    printf("Parent collected Child-1\n");

    // Do NOT wait for Child-2
    printf("Parent exiting...\n");

    exit(0);
}   