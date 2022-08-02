#include <string.h>
#include <errno.h>
#include <netinet/in.h>

#include "rpc/stub/rpc_stub.h"
#include "socket.h"

/**
 * @brief The common tools for tunneling 'ssh', 'chisel' (awesome tool check it out) and 'proxychains',
 *  are using a similar represantion to the remoted port that will be tunneled to a localport.
 * 
 *  When Tunneling you always have a local ip and port that will be forwarded to a remote ip and port.
 * 
 *  This struct represets an ip and port.
 * 
 */
struct IPTunnel {
    int port;
    char address[15];
};

/**
 * @brief The struct is a representation of the tunnel.
 * 
 * The local (IPTunnel) is from the attacker perspective, lets say the attacker want that localhost:50 will be used for the tunnel, he will set that in the local variable.
 * The remote (IPTunnel) is from the target perspective, lets say the attacker want to access remote:3000, he will set that in the remote variable.
 * reversed (boolean) should the tunnel be reversed, be careful the tunnel is already reversed because the entire stream is reversed.  
 * tunnel_port the port that the tunnel will be set for.
 * 
 */
struct RPCTunnel {
    int function_id;
    struct IPTunnel local; // The attacker perspective.
    struct IPTunnel remote; // The target perpective.
    int tunnel_port; 
    int reversed; // whether the connection should be a reverse tunnel or not.
    char null_bytes[4096 - (2*sizeof(int)) - (2*sizeof(struct IPTunnel))];
};

int rpc_tunnel(struct RPC rpc);