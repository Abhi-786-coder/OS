#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

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

    int shmid = shmget(key, sizeof(struct student), 0666);

    struct student *s = (struct student*) shmat(shmid, NULL, 0);

    // Compute total
    s->total = s->marks[0] + s->marks[1] + s->marks[2];

    // Compute percentage
    s->percentage = s->total / 3.0;

    // Assign grade
    if (s->percentage >= 75)
    {
        s->grade = 'A';
    }
    else if (s->percentage >= 60)
    {
        s->grade = 'B';
    }
    else if (s->percentage >= 50)
    {
        s->grade = 'C';
    }
    else
    {
        s->grade = 'F';
    }

    printf("\n--- Result ---\n");
    printf("Name: %s\n", s->name);
    printf("Total: %d\n", s->total);
    printf("Percentage: %.2f\n", s->percentage);
    printf("Grade: %c\n", s->grade);

    shmdt(s);

    // Optional cleanup (only run once)
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}