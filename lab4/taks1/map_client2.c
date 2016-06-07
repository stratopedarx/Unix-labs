#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>


int main()
{
	char buf[30];
	int fd = shm_open("/friday", O_RDONLY, 0750); // created instance of shared memory
	strcpy(buf, (char *)mmap(NULL, sizeof(buf), PROT_READ, MAP_SHARED, fd, 0));
	printf("%s\n", buf);
	getchar();
	return 0;
}