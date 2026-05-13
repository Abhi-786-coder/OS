#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

struct student
{
    char name[50];
    int marks[3];
    int total;
    float percentage;
    char grade;
};

int main()
{
    key_t key = ftok("shmfile", 65);

    int shmid = shmget(key, sizeof(struct student), 0666 | IPC_CREAT);

    struct student *s = (struct student*) shmat(shmid, NULL, 0);

    printf("Enter name: ");
    scanf("%s", s->name);

    printf("Enter 3 subject marks:\n");
    for (int i = 0; i < 3; i++)
    {
        scanf("%d", &s->marks[i]);
    }

    printf("\nData stored in shared memory.\n");

    shmdt(s);
    return 0;
}