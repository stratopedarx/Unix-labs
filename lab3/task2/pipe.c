#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#define SIZE 2

int main()
{
	int fd[SIZE];
	char buf_in[] = "Hello world\n";
	char buf_out[2048];
	pid_t child;
	pipe(fd);
	child = fork();
	if(child == 0)
	{	
		close(fd[0]);
		write(fd[1], buf_in, sizeof(buf_in));
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		read(fd[0], buf_out, 2048);
		close(fd[0]);
		printf("%s\n", buf_out);	
	}
	return 0;
}
