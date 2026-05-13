#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>

int main()
{
    FILE *fp;
    int fd;
    char name[50];
    int marks;

    fp = fopen("students.txt", "a+"); // append + read
    if(fp == NULL)
    {
        perror("File open failed");
        return 1;
    }

    fd = fileno(fp);

    printf("Writer: Trying to acquire exclusive lock...\n");
    flock(fd, LOCK_EX);
    printf("Writer: Lock acquired.\n");

    printf("Enter student name and marks to add: ");
    scanf("%s %d", name, &marks);

    fprintf(fp, "%s %d\n", name, marks);
    printf("Writer: Record added.\n");

    printf("Writer: Sleeping for 10 seconds...\n");
    sleep(10);

    flock(fd, LOCK_UN);
    printf("Writer: Lock released.\n");

    fclose(fp);
    return 0;
}



// File *fp
// int fd
// fp = fopen("students.txt", "a+")
// fd = fileno(fp)
//flock(fd, LOCK_EX)
//fprintf(fp, "%s" "%d\n", name,marks);
//sleep(10);

// flock(fd,LOCK_UN);
//fclose(fp);
// return 0