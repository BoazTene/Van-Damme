#include "rpc/stub/rpc_stub.h"

unsigned char* serialize(const struct Result result);
unsigned char* svc_handler(const struct RPC rpc);
const struct RPC deserialize(unsigned char *buff);
const struct RPC recv_rpc_message(int fd_socket);

/**
 * @brief The main rpc function, waits for new results from the server and calls the right function. 
 * 
 * @param fd_socket 
 * @return int 
 */
int svc_create(int fd_socket) {
    while (1) {
        const struct RPC rpc = recv_rpc_message(fd_socket);
        printf("sdfsdfdsf\n");
        int child_pid = fork();

        // checking whether its the parent process.
        if (child_pid > 0) {
            continue;
        } else if(child_pid < 0) { // making sure the fork syscall didn't returned any errors.
            continue;
        }

        printf("Child is printing\n");

        unsigned char* result = svc_handler(rpc);
        printf("%s\n", result);
        send(fd_socket, &result, sizeof(result), MSG_CONFIRM);
    }

    return 0;
}

/**
 * @brief Handles RPC request, calls the right function and returns the right result. 
 * 
 * @param rpc 
 * @return unsigned* 
 */
unsigned char* svc_handler(const struct RPC rpc) {
    printf("The %d function has been called!", rpc.func_id);

    struct Result result = {status: 1, data: "hello world"};

    if (rpc.func_id == SHELL) { // shell function id.
        rpc_shell(rpc);
    } else if (rpc.func_id == TUNNEL) { // tunnel function id.
        rpc_tunnel(rpc);
    }

    return serialize(result);
}

/**
 * @brief Recieves an RPC request from the server. 
 * 
 * @param fd_socket 
 * @return const struct RPC 
 */
const struct RPC recv_rpc_message(int fd_socket) {
    unsigned char buff[sizeof(struct RPC)];

    recv(fd_socket, &buff, sizeof(buff), MSG_WAITALL);

    return (struct RPC) deserialize(buff);
}

/**
 * @brief Basic deserialize function for the RPC struct. 
 * 
 * @param buff 
 * @return const struct RPC 
 */
const struct RPC deserialize(unsigned char *buff) {
    struct RPC *rpc_message = (struct RPC*) buff;

    return *rpc_message;
}

/**
 * @brief Basic serialize function for the Result struct. 
 * 
 * @param result 
 * @return unsigned* 
 */
unsigned char* serialize(const struct Result result) {
    ssize_t size = sizeof(struct Result);

    char buff[size];
    memset(buff, 0x00, size);
    memcpy(buff, &result, size);
    
    return buff;
}