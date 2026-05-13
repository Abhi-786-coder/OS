#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>

int main()
{
    FILE *fp;
    int fd;
    char name[50];
    int marks, total = 0, count = 0;

    fp = fopen("students.txt", "r");
    if(fp == NULL)
    {
        perror("File open failed");
        return 1;
    }

    fd = fileno(fp);

    printf("Reader AVG: Trying to acquire shared lock...\n");
    flock(fd, LOCK_SH);
    printf("Reader AVG: Lock acquired.\n");

    // Read file
    while(fscanf(fp, "%s %d", name, &marks) != EOF)
    {
        total += marks;
        count++;
    }

    if(count > 0)
        printf("Reader AVG: Average = %.2f\n", (float)total/count);

    printf("Reader AVG: Sleeping for 10 seconds...\n");
    sleep(10);

    flock(fd, LOCK_UN);
    printf("Reader AVG: Lock released.\n");

    fclose(fp);
    return 0;
}