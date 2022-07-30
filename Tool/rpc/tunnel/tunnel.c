#include "rpc/tunnel/tunnel.h"

struct RPCTunnel tunnel_deserialize(const struct RPC rpc);

int rpc_tunnel(struct RPC rpc) {
    struct RPCTunnel tunnel = tunnel_deserialize(rpc);

    printf("local: %d, %s, remote %d, %s \n", tunnel.local.port, tunnel.local.address, tunnel.remote.port, tunnel.remote.address);
    printf("tunnel_port: %d\nreversed: %d\nnull_bytes: %s\n", tunnel.tunnel_port, tunnel.reversed, tunnel.null_bytes);

    return 0;
}

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