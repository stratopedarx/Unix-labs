#include <signal.h>
#include <stdio.h>

void handler(int sig)
{
	printf("WTF\n");
}



int main()
{
	while(1)
		signal(SIGINT, handler);  // SIGINT are send the system

	return 0;
}