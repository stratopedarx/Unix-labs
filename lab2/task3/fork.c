#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main()
{
    pid_t child;
    
child = fork();   
if (child==0){
        printf("I am child %d\n", getpid());
	printf("I am id child %d\n", getuid());
    }
    else{
        printf("I am parent %d\n", getpid());
	printf("I am parent uis %d\n", getuid());
    }

return 0;
}
