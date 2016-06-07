#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>

int main()
{
	sem_t *pointer = sem_open("SEMA", O_CREAT | O_RDWR, 0750, 3);
	sem_wait(pointer);
	printf("I am critical sections %d\t%d\n", getpid(), getppid());
	getchar();
	sem_post(pointer);
	return 0;
}