#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>

int main()
{
    FILE *fp = fopen("inventory.txt", "r");
    if(fp == NULL)
    {
        printf("File not found. Run writer first.\n");
        return 1;
    }

    int fd = fileno(fp);

    printf("Reader: Trying for shared lock...\n");
    flock(fd, LOCK_SH);
    printf("Reader: Lock acquired\n");

    printf("\n--- Inventory ---\n");

    char ch;
    while((ch = fgetc(fp)) != EOF)
        putchar(ch);

    printf("\n-----------------\n");

    sleep(10); // for demo

    flock(fd, LOCK_UN);
    printf("Reader: Lock released\n");

    fclose(fp);
    return 0;
}