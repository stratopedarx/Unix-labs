#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>


int main()
{
    if(fork() == 0)
    {
        puts("I am child №1\n");
        printf("I have pid: %d\n", getpid());
        printf("My parent has ppid %d\n", getppid());
        execl("/bin/echo", "/bin/echo", "I message one", (char *)0);
    }
    if(fork() == 0)
    {
        puts("I am child №2\n");
        printf("I have pid: %d\n", getpid());
        printf("My parent has ppid %d\n", getppid());
        execl("/bin/echo", "/bin/echo", "I message two", (char *)0);     
    }
    if(fork() == 0)
    {
        puts("I am child №3\n");
        printf("I have pid: %d\n", getpid());
        printf("My parent has ppid %d\n", getppid());
        execl("/bin/echo", "/bin/echo", "I message three", (char *)0);
    }

    puts("I am parent\n");
    printf("I have pid: %d\n", getpid()); 
    return 0;
}
