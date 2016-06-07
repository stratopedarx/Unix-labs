#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

int count;
pthread_mutex_t mutex;
pthread_cond_t cond;


void writer()
{
	while(count < 100)
	{
		pthread_mutex_lock(&mutex);
		count++;
		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&cond);
		sleep(1);
	}
	printf("Exited %d\n", (int)pthread_self());
}	


void drower()
{
	while(count < 100)
	{
		pthread_mutex_lock(&mutex);
		printf("Progress %d in thread %d\n", count, (int)pthread_self());
		pthread_cond_wait(&cond, &mutex);
		pthread_mutex_unlock(&mutex);
	}
	printf("Exited %d\n", (int)pthread_self());
}	

int main()
{
	pthread_t thread1, thread2;
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);
	pthread_create(&thread1, NULL,(void *(*)(void *))writer, NULL);
	pthread_create(&thread2, NULL,(void *(*)(void *))drower, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	return 0;
}