#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	pid_t child;
	if(argc <2)
	{
		printf("Invalid input data. Use paramentes\n");
		puts("Use for example :$ execv </bin/ls> <parametres>\n");
		exit(1);
	}
	child = fork();
	if (child == 0)
	{
		execv(argv[1], argv);
		perror("Error with child\n");
		exit(2);
	}
	else
	{
		wait(&child);
		printf("Return %i\n", WEXITSTATUS(child));
	}
	return 0;

}
