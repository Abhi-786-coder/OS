#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>

int main()
{
	FILE* fp  = fopen("server.log", "a"); // fopen a does is append to the file if exists or creates one if doesnt exist
	int fd = fileno(fp);

	printf("Writer: Trying for exclusive lock...\n");
	flock(fd, LOCK_EX);
	printf("Writer: Lock Acquired\n");

	printf("Enter log message: ");
	char log[100];
	getchar();
	fgets(log, sizeof(log), stdin);


	fprintf(fp, "%s", log);
	printf("Writer Log Written..\n");

	printf("Writer sleeping...\n");
	sleep(10);

	flock(fd, LOCK_UN);
	printf("Writer: Lock released...\n");


	fclose(fp);
	return 0;
}