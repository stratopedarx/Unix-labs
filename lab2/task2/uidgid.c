#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main()
{
	printf("%d\t%d\n", getuid(), getgid());
	return 0;
}