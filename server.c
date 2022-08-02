#include <stdio.h>

#include "socket.h"

#define NUMBER_OF_CLIENTS 1

static const char* ip = "0.0.0.0";

int main(int argc, char const *argv[])
{
    printf("Creating socket instance...\n");

    int server_fd = create_socket();
    struct sockaddr_in address = create_sockaddr(ip, PORT);
    struct sockaddr_in client;

    if (start_server(server_fd, address, sizeof(address)) == -1) {
        perror("Server creation failed.\n");
        return -1;
    }

    printf("Starting server...\n");

    int client_size = sizeof(client);

    while (1) {
        int client_fd = accept(server_fd, (struct sockaddr*)&client, &client_size);
        printf("A client just connected\n");

        close(client_fd);
    }
    
    return 0;
}
