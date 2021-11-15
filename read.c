#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	char *c = (char *) calloc(100, sizeof(char));
	int fd = open("foo.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("fd");
		exit(1);
	}
	int sz = read(fd, c, 14);
	printf("called read(%d, c, 14). returned %d bytes were read.\n", fd, sz);
	c[sz] = '\0';
	printf("c = %s\n", c);
	return 0;
}
