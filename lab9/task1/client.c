#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>


int main(int argc, char const *argv[])
{
	int fd_sock, temp_sock;
	char buf[] = "Hello dear server\n";
	char temp[1024];
	struct sockaddr_in my_client;
	struct hostent *myhost;

	fd_sock = socket(AF_INET, SOCK_STREAM, 0);
	memset(&my_client, 0, sizeof(my_client)); // initialize struct
	my_client.sin_family = AF_INET;
	my_client.sin_port = htons(1731);
	myhost = gethostbyname("localhost");
	memcpy(&my_client.sin_addr.s_addr, myhost->h_addr, myhost->h_length);

	connect(fd_sock, &my_client, sizeof(my_client));
	write(fd_sock, buf, sizeof(buf));
	read(fd_sock, temp, sizeof(temp));
	printf("%s\n", temp);
	close(fd_sock);
	return 0;
}