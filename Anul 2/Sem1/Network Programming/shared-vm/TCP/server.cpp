#include <iostream>
#include <string.h>
#include <netinet/in.h>

#define PORT 6767

int main(int argc, char* argv[]) {
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	int socket = socket(AF_INET, SOCK_STREAM, 0);

	setsockopt(socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	bind(socket, (struct sockaddr_in*)&address, sizeof(address));

	listen(socket, 3);

	int connectionAcceptedSocket = accept(socket, (struct sockaddr_in*)&address, (sock_len_t*)&addrlen);

	char buffer[128] = { 0 };
	int valread = read(new_socket, buffer, 1024);
	printf("%s\n", buffer);
	send(new_socket, "hi", 2, 0);
	return 0;
}