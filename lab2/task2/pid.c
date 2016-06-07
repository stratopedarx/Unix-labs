#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main()
{
    printf("%d\t%d\n", getpid(), getppid());
    return 0;
}
