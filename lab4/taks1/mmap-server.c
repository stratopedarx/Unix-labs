#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

int main()
{
	char buf[] = "I am hangry. The day of the Dead\n";
	int fd = shm_open("/friday", O_CREAT | O_RDWR, 0750); // created instance of shared memory
	// The instance of shared memory have 0 len, so use ftruncate for upper len of instance
	ftruncate(fd, 2048);
	strcpy((char *)mmap(NULL, sizeof(buf), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0), buf);
	getchar();
	shm_unlink("/friday");
	return 0;
}