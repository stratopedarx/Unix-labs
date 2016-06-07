#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main()
{
    execl("/bin/cat", "/bin/cat", "/home/stratopedarx/Unix/labs/lab2/task4/mycat.c", NULL);
    execl("/bin/cat", "/bin/cat", "./mycat.c", (char *)0);
    return 0;
}

