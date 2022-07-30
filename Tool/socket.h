#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>

#define PROTOCOL 6 // tcp protocol.
#define PORT 9002

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