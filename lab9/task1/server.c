#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>


int main(int argc, char const *argv[])
{
	int fd_sock, temp_sock, s;
	char buf[] = "Hello dear client\n";
	char temp[1024];
	struct sockaddr_in my_ser, my_client;

	memset(&my_ser, 0, sizeof(my_ser)); // initialize struct
	fd_sock = socket(AF_INET, SOCK_STREAM, 0);
	my_ser.sin_family = AF_INET;
	my_ser.sin_port = htons(1731);
	my_ser.sin_addr.s_addr = INADDR_ANY;

	if(bind(fd_sock, &my_ser, sizeof(my_ser)) < 0)
	{
		perror("Mistake");
		exit(1);
	}
	listen(fd_sock, 5);
	s = sizeof(my_client);
	while(1)
	{
		temp_sock = accept(fd_sock, &my_client, &s);
		close(fd_sock);
		read(temp_sock, temp, sizeof(temp));
		printf("%s\n", temp);
		write(temp_sock, buf, sizeof(buf));
		close(temp_sock);
	}
	return 0;
}