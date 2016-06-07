#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void handler()
{
	while(1)
	{
		printf("Thread %d\n", pthread_self());
		sleep(1);
	}
}	

int main()
{
	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL,(void *(*)(void *))handler, NULL);
	pthread_create(&thread2, NULL,(void *(*)(void *))handler, NULL);
	pthread_join(thread1, NULL); // ждет когда закончится поток
	pthread_join(thread2, NULL); // если не будет то главный поток мэйн завершит всё
	return 0;
}