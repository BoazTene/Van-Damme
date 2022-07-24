#include <stdio.h>

#include "socket.h"
#include "rpc/stub/rpc_stub.h"

int main(int argc, char const *argv[])
{
    int socket_fd = create_socket();

    if (connect_socket(socket_fd, "localhost") == -1) {
        printf("The socket connection failed.");

        exit(EXIT_FAILURE);
    } 

    svc_create(socket_fd);

    return 0;
}
