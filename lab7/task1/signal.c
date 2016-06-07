#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void (*react)();

void handler(int i)
{ 
	extern void (*react)();
	static int count = 0;
	printf("Handler %d\n", count++);
	if (count == 5)
	{
		printf("%d\n", *react);
		signal (SIGINT, react);
	}
}


int main()
{
	extern void (*react)();
	while(1)
		if ((react = signal(SIGINT, handler)) == SIG_IGN)
	        signal (SIGINT, SIG_IGN);
	// signal (SIGINT, SIG_DFL);
	return 0;
}