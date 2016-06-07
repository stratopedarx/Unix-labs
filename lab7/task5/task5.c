#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int count = 0;
void(*p)(int);



void handler(int sig)
{
	int stat;
	pid_t pid = waitpid(-1, &stat, 0);
	if((stat & 0x7f) == 0)
		printf("Child is dead %d\n, %d", pid, (stat & 0x7f));
	if((stat & 0xff00) == 0)	
		printf("Child is dead %d, %d\n", pid, (stat & 0xff00)>>8);
}


int main()
{
	pid_t child;
	signal(SIGCHLD, handler);  // sign up on the signal
	
	child = fork();
	if (child == 0)
		exit(150);
	child = fork();
	if (child == 0)
		while(1);
	while(1);
	return 0;
}