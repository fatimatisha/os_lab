#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{	int fd = creat("foo.txt", S_IRWXU);
	if (fd == -1)
	{
		printf("file is already created!");
		perror("fd");
		exit(1);
	}
	printf("file created successfully\n");
	return 0;
}
