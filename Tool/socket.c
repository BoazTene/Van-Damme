#include "socket.h" 

/**
 * @brief Create a socket object
 * 
 * @return int 
 */
int create_socket() {
    int socket_fd = socket(AF_INET, SOCK_STREAM, PROTOCOL);

    if (socket_fd == 0) {
        perror("Socket creation failed.");

        exit(EXIT_FAILURE);
    }

    return socket_fd;
}

/**
 * @brief Connect to the remote server. 
 * 
 * @param socket_fd The socket file descriptor. 
 * @param ip The ip of the remote server, for example: 192.168.1.1 
 * @return int 0 on success, see man connect for details. 
 */
int connect_socket(int socket_fd, char *ip) {
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    inet_aton(ip, &address.sin_addr.s_addr);

    return connect(socket_fd, &address, sizeof(address));
}

