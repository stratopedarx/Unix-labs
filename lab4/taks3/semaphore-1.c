#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#define SIZE 50


void zero_without_n(char *arr);
void fill_arr_with_zero(char *arr, int N);

int main()
{
    pid_t child;
    int i = 0;
    int shm;
    char buf_ch[SIZE] = { 0 };
    char buf_pr[SIZE] = { 0 };
    char message[][SIZE] = {"Children in CS %d\n", "Children out CS\n",
							"Parent in CS %d\n", "Parent out CS\n"};

	sem_t *pointer = sem_open("SEMA", O_CREAT | O_RDWR, 0750, 3);
	child = fork();
	while(i < 20)
	{
		if (child==0)
		{
			//sleep(1);
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
        	strcpy(buf_ch, (char *)mmap(NULL, sizeof(buf_ch), PROT_READ, MAP_SHARED, shm, 0));
			printf(buf_ch);	   // Parent out CS
			fflush(stdout);
			fill_arr_with_zero(buf_ch, SIZE);    // clean the arr

        	sem_wait(pointer);		   // create the critical situation
        	printf(message[0], shm);   // Children in CS
			fflush(stdout);
			sem_post(pointer);		   // close CS
			printf(message[1]);        // Children out CS
			//strcpy((char *)mmap(NULL, sizeof(message[1]), PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0), message[1]);
			//strcpy(buf_ch, (char *)mmap(NULL, sizeof(buf), PROT_READ, MAP_SHARED, shm, 0));
			//printf(buf_ch);	// Parent in CS
			//fflush(stdout);
			//fill_arr_with_zero(buf_ch);
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
			// strcpy(buf_pr, (char *)mmap(NULL, sizeof(buf_pr), PROT_READ, MAP_SHARED, shm, 0));
			// printf(buf_pr);	 // Children out CS
			// fflush(stdout);

			sem_wait(pointer);		   // create the critical situation
			printf(message[2], shm);   // Parent in CS
			fflush(stdout);
			//strcpy((char *)mmap(NULL, sizeof(message[2]), PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0), message[2]);
			sem_post(pointer);		   // close CS
			strcpy((char *)mmap(NULL, sizeof(message[3]), PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0), message[3]);
	    	//shm_unlink("TASK4");
	    }
	    sleep(1);
	    i++;
	}
    getchar();
    shm_unlink("TASK4");
    sem_close(pointer);
    sem_destroy(pointer);
	return 0;
}


void zero_without_n(char *arr)
{
	if (arr[strlen(arr) - 1] == '\n')
		arr[strlen(arr) - 1] = '\0';
	return;
}

void fill_arr_with_zero(char *arr, int N)
{
	int i;
	for( i = 0; i < N; i++)
		arr[i] = 0;
	return;
}