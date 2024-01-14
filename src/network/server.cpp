#include <iostream>
#include <cstring>
#include "../../includes/block.h"
#include "settings.h"

void handle_on_connection(int client_socket)
{
    char buffer[1024] = {0};
    ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

    if (bytes_received == -1) {
        perror("recv");
    } else if (bytes_received > 0) {
        std::cout << "Received data from client:\n";
        std::cout.write(buffer, bytes_received);
    }

    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr = {0};
    socklen_t addr_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket == -1) {
        perror("socket");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        close(server_socket);
        return 1;
    }

    if (listen(server_socket, 5) == -1) {
        perror("listen");
        close(server_socket);
        return 1;
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    while (true) {
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_len);

        if (client_socket == -1) {
            perror("accept");
        } else {
            handle_on_connection(client_socket);
        }
    }

    close(server_socket);

    return 0;
}

