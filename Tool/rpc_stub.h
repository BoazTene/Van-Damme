#include <sys/socket.h>
#include <string.h>

/**
 * @brief The base structure of an RPC call.
 * 
 * Note that the argument's size is 4092, because almost every network card supports 4096 bytes.
 */
struct RPC {
    int function_id;
    unsigned char arguments[4096 - sizeof(int)];
};

/**
 * @brief The base structore of an RPC result. 
 * 
 * Note that the argument's size is 4092, becuase almost every network card supports 4096 bytes.
 */
struct Result {
    int status;
    unsigned char data[4096 - sizeof(int)]
};

/**
 * @brief The main rpc function, waits for new results from the server and calls the right function. 
 * 
 * @param fd_socket 
 * @return int 
 */
int svc_create(int fd_socket);