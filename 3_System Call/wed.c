#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main()
{
    pid_t pid1, pid2;

    // Print current time
    time_t now;
    time(&now);
    printf("Parent started (PID: %d)\n", getpid());
    printf("Current Time: %s\n", ctime(&now));

    // -------- Child 1 --------
    pid1 = fork();

    if(pid1 == 0)
    {
        printf("Child-1 (PID: %d) executing date\n", getpid());
        execlp("date", "date", NULL);

        perror("exec failed");
        exit(1);
    }

    // -------- Child 2 --------
    pid2 = fork();

    if(pid2 == 0)
    {
        printf("Child-2 started (PID: %d, PPID: %d)\n", getpid(), getppid());

        sleep(15);  // LONG sleep → ensures orphan

        printf("Child-2 after sleep (PID: %d, NEW PPID: %d)\n", getpid(), getppid());

        exit(0);
    }

    // -------- Parent --------

    // Wait ONLY for child-1
    waitpid(pid1, NULL, 0);
    printf("Child-1 finished\n");

    // Sleep a bit so you can observe processes
    printf("Parent sleeping for 5 seconds (observe zombie/orphan now!)\n");
    sleep(5);

    printf("Parent exiting NOW (Child-2 will become orphan)\n");

    return 0;
}