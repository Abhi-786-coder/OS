#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>
#include <string.h>

int main()
{
    FILE *fp;
    int fd;
    char name[50], topper[50];
    int marks, max = -1;

    fp = fopen("students.txt", "r");
    if(fp == NULL)
    {
        perror("File open failed");
        return 1;
    }

    fd = fileno(fp);

    printf("Reader TOPPER: Trying to acquire shared lock...\n");
    flock(fd, LOCK_SH);
    printf("Reader TOPPER: Lock acquired.\n");

    while(fscanf(fp, "%s %d", name, &marks) != EOF)
    {
        if(marks > max)
        {
            max = marks;
            strcpy(topper, name);
        }
    }

    printf("Reader TOPPER: Topper = %s (%d)\n", topper, max);

    printf("Reader TOPPER: Sleeping for 10 seconds...\n");
    sleep(10);

    flock(fd, LOCK_UN);
    printf("Reader TOPPER: Lock released.\n");

    fclose(fp);
    return 0;
}