#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

struct data
{
    int number;
    int result;
};

int main()
{
    key_t key = ftok("shmfile", 75);

    int shmid = shmget(key, sizeof(struct data), 0666 | IPC_CREAT);

    struct data *d = (struct data*) shmat(shmid, NULL, 0);

    pid_t pid = fork();

    if (pid > 0)
    {
        // Parent = Producer
        printf("Enter number: ");
        scanf("%d", &d->number);

        printf("Parent produced number = %d\n", d->number);

        wait(NULL); // wait for child

        printf("Parent reads result = %d\n", d->result);

        shmdt(d);
        shmctl(shmid, IPC_RMID, NULL);
    }
    else
    {
        // Child = Consumer
        sleep(1); // ensure parent writes first

        printf("Child reads number = %d\n", d->number);

        d->result = d->number * d->number;

        printf("Child computed square = %d\n", d->result);

        shmdt(d);
    }

    return 0;
}