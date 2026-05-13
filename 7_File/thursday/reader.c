#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>

int main()
{
    FILE *fp = fopen("server.log", "r");
    int fd = fileno(fp);

    printf("Analyzer: Trying for shared lock...\n");
    flock(fd, LOCK_SH);
    printf("Analyzer: Lock acquired\n");

    printf("Analyzer: Reading logs...\n");

    char ch;
    while((ch = fgetc(fp)) != EOF)
        putchar(ch);

    printf("\nAnalyzer: Sleeping...\n");
    sleep(10);

    flock(fd, LOCK_UN);
    printf("Analyzer: Lock released\n");

    fclose(fp);
    return 0;
}