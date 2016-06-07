#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <fcntl.h>
#define SIZE 50


int main()
{
    pid_t child;
    int i = 0;
    int shm;
    char buf[SIZE];
    char message[][SIZE] = {"Children in CS %d\n", "Children out CS\n",
							"Parent in CS %d\n", "Parent out CS\n"};

	sem_t *pointer = sem_open("SEMA", O_CREAT | O_RDWR, 0750, 3);

	while(i < 20)
	{
		if (child==0)
		{
			sleep(1);
			if ((shm = shm_open("/TASK4", O_RDONLY, 0750)) == -1)
			{
	       		perror("shm_open");
        		return 1;
        	}
        	if (ftruncate(shm, 30) == -1) 
        	{
            	perror("ftruncate");
            	return 1;
        	}
        	sem_wait(pointer);		   // create the critical situation
        	printf(message[0], shm);   // Children in CS
			fflush(stdout);
			sem_post(pointer);		   // close CS
			printf(message[0], shm);   // Children out CS

			strcpy(buf, (char *)mmap(NULL, sizeof(buf), PROT_READ, MAP_SHARED, shm, 0));
			printf(buf);	// Parent in CS
			fflush(stdout);
			buf = 0;
			strcpy(buf, (char *)mmap(NULL, sizeof(buf), PROT_READ, MAP_SHARED, shm, 0));
			printf(buf);	// Parent out CS
			fflush(stdout);

			shm_unlink("TASK4");
    	}

	    else
	    {
	    	if ((shm = shm_open("/TASK4", O_CREAT | O_RDWR, 0750)) == -1)
			{
	       		perror("shm_open");
        		return 1;
        	}
        	if (ftruncate(shm, 30) == -1) 
        	{
            	perror("ftruncate");
            	return 1;
        	}
			sem_wait(pointer);
			strcpy((char *)mmap(NULL, sizeof(message[2]), PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0), message[2]);
			sem_post(pointer);
			sleep(1);
			strcpy((char *)mmap(NULL, sizeof(message[3]), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0), message[3]);
	    	shm_unlink("TASK4");
	    }
	    i++;
	}
    getchar();
    sem_close(pointer);
    sem_destroy(pointer);
	return 0;
}

