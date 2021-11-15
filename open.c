#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int fd = open("foo.txt", O_RDONLY);
	printf("fd = %d\n", fd);
	if (fd == -1)
	{
		perror("fd");
		exit(1);
	}
	printf("file opened successfully\n");
	return 0;
}
