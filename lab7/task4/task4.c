#include <signal.h>
#include <stdio.h>

int count = 0;
void(*p)(int);



void handler(int sig)
{
	if (count == 5)
		signal(SIGINT, p);
	else
		printf("WTF\n %d", count++);
}


int main()
{
	void(*p)(int);
	p = signal(SIGINT, handler);
	while(1);
		
		//signal(SIGINT, handler)
		//signal(SIGINT, handler);  // SIG_INT are send the system

	return 0;
}