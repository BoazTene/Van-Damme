#include <stdio.h>

#include "socket.h"

#define NUMBER_OF_CLIENTS 1

static const char* ip = "0.0.0.0";

int main(int argc, char const *argv[])
{
    printf("Creating socket instance...\n");

    int server_fd = create_socket();
    struct sockaddr_in address = create_sockaddr(ip, PORT);

    if (start_server(server_fd, address, sizeof(address)) == -1) {
        perror("Server creation failed.\n");
        return -1;
    }

    printf("Starting server...\n");

    while (1) {
        struct sockaddr_in client_sockaddr;
        int c_size = sizeof(client_sockaddr);
        int client_fd = accept(server_fd, &client_sockaddr, &c_size);
        struct Address address = create_address(client_sockaddr);

        printf("Client just connected (%s, %d)\n", address.ip, address.port);

        close(client_fd);
    }
    
    return 0;
}
