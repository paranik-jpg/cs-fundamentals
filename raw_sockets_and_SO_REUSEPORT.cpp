#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cerrno>

int main(int argc, char* argv[]) {
    bool enable_reuse = false;
    if (argc > 1 && std::string(argv[1]) == "-r") {
        enable_reuse = true;
    }

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "[PID " << getpid() << "] socket() failed: " << strerror(errno) << "\n";
        return 1;
    }

    if (enable_reuse) {
        int opt = 1;
        // SO_REUSEADDR: Bypasses TIME_WAIT state binding conflicts
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
            std::cerr << "[PID " << getpid() << "] setsockopt(SO_REUSEADDR) failed: " << strerror(errno) << "\n";
            close(server_fd);
            return 1;
        }
        // SO_REUSEPORT: Allows multiple sockets to bind the exact same IP:PORT tuple
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
            std::cerr << "[PID " << getpid() << "] setsockopt(SO_REUSEPORT) failed: " << strerror(errno) << "\n";
            close(server_fd);
            return 1;
        }
        std::cout << "[PID " << getpid() << "] SO_REUSEPORT & SO_REUSEADDR enabled.\n";
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "[PID " << getpid() << "] bind() FAILED: " << strerror(errno)
                  << " (errno: " << errno << ")\n";
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 10) < 0) {
        std::cerr << "[PID " << getpid() << "] listen() failed: " << strerror(errno) << "\n";
        close(server_fd);
        return 1;
    }

    std::cout << "[PID " << getpid() << "] Successfully bound & listening on port 8080...\n";

    // Block on accept() to hold the port active
    sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);
    int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
    if (client_fd >= 0) {
        std::cout << "[PID " << getpid() << "] Accepted incoming connection.\n";
        close(client_fd);
    }

    close(server_fd);
    return 0;
}
