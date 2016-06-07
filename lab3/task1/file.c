#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>


int main()
{
	char buf[] = "Hello world\n";
	int fd1;
	int fd = open("./hello.txt", O_CREAT | O_WRONLY, 0755);
	printf("%d\n", fd);
	fd1 = open("./hello2.txt", O_CREAT | O_WRONLY, 0755);
	printf("%d\n", fd1);
	write(fd, buf, sizeof(buf));
	close(fd);
	fd = open("./hello.txt", O_RDONLY);
	printf("%d\n", fd);
	read(fd, buf, 2048);
	printf("%s\n", buf);
	close(fd);
	return 0;
}