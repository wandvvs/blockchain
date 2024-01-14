#include "../includes/blockchain.h"
#include "network/socket.h"

int main() {
    int client_socket = createClientSocket();

    Blockchain chain;
    Block block;

    chain.add(block);

    block.tcp_send_block(client_socket);
}
