#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "socket() failed: " << strerror(errno) << "\n";
        return 1;
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "bind() failed: " << strerror(errno) << "\n";
        close(server_fd);
        return 1;
    }

    // Explicitly clamp the backlog queue to 1 slot
    if (listen(server_fd, 1) < 0) {
        std::cerr << "listen() failed: " << strerror(errno) << "\n";
        close(server_fd);
        return 1;
    }

    std::cout << "[PID " << getpid() << "] Listening on port 8080 with backlog = 1.\n";
    std::cout << "[PID " << getpid() << "] Intentionally avoiding accept(). Sleeping forever...\n";

    // Block process execution so no connections are ever dequeued
    while (true) {
        pause();
    }

    close(server_fd);
    return 0;
}
