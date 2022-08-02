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
 * @brief Create a sockaddr object
 * 
 * @param ip 
 * @param port 
 * @return struct sockaddr_in 
 */
struct sockaddr_in create_sockaddr(char *ip, int port) {
    struct sockaddr_in address;
    
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    inet_aton(ip, &address.sin_addr.s_addr);

    return address;
}

/**
 * @brief Create a address object from and sockaddr_in object
 * 
 * @param sockaddr 
 * @return struct Address 
 */
struct Address create_address(struct sockaddr_in sockaddr) {
    struct Address address;

    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &sockaddr.sin_addr, ip, INET_ADDRSTRLEN);
   
    address.port = ntohs(sockaddr.sin_port);
    strcpy(address.ip, ip);

    return address;
}

/**
 * @brief Connect to the remote server. 
 * 
 * @param socket_fd The socket file descriptor. 
 * @param ip The ip of the remote server, for example: 192.168.1.1 
 * @return int 0 on success, see man connect for details. 
 */
int connect_socket(int socket_fd, char *ip, int port) {
    struct sockaddr_in address = create_sockaddr(ip, port);

    return connect(socket_fd, &address, sizeof(address));
}

/**
 * @brief Starts a socket server (binds + listen).
 * 
 * @param socket_fd 
 * @return int 
 */
int start_server(int socket_fd, struct sockaddr_in address, int address_size) {
    if (bind(socket_fd, &address, address_size) < 0) { 
        return -1;
    }

    if (listen(socket_fd, 5) < 0) {
        return -1;
    }

    return 0;
}