#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>

#define PROTOCOL 6 // tcp protocol.
#define PORT 9002

struct Address {
    char ip[INET_ADDRSTRLEN];
    int port;
};

/**
 * @brief Create a socket object
 * 
 * @return int 
 */
int create_socket();

/**
 * @brief Connect to the remote server. 
 * 
 * @param socket_fd The socket file descriptor. 
 * @param ip The ip of the remote server, for example: 192.168.1.1 
 * @return int 0 on success, see man connect for details. 
 */
int connect_socket(int socket_fd, char *ip, int port);

/**
 * @brief Create a sockaddr object
 * 
 * @param ip 
 * @param port 
 * @return struct sockaddr_in 
 */
struct sockaddr_in create_sockaddr(char *ip, int port);

/**
 * @brief Create a address object from and sockaddr_in object
 * 
 * @param sockaddr 
 * @return struct Address 
 */
struct Address create_address(struct sockaddr_in sockaddr);

/**
 * @brief Starts a socket server (binds + listen).
 * 
 * @param socket_fd 
 * @param ip 
 * @param port 
 * @return int 
 */
int start_server(int socket_fd, struct sockaddr_in address, int address_size);