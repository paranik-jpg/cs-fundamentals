#include <iostream>
#include <string>
#include <sstream>
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

    if (listen(server_fd, 10) < 0) {
        std::cerr << "listen() failed: " << strerror(errno) << "\n";
        close(server_fd);
        return 1;
    }

    std::cout << "[HTTP Server] Listening on http://127.0.0.1:8080 ...\n";

    while (true) {
        sockaddr_in client_addr{};
        socklen_t client_len = sizeof(client_addr);

        // Accept incoming client connection
        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd < 0) {
            std::cerr << "accept() failed: " << strerror(errno) << "\n";
            continue;
        }

        // --- THE ATTACK: Blocking recv() into a string buffer ---
        char buffer[4096];
        std::memset(buffer, 0, sizeof(buffer));

        ssize_t bytes_read = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
        if (bytes_read <= 0) {
            close(client_fd);
            continue;
        }

        std::string raw_request(buffer, bytes_read);

        // --- THE AUTOPSY: Parse raw HTTP request line & isolate URI ---
        std::istringstream stream(raw_request);
        std::string method, uri, version;
        stream >> method >> uri >> version;

        std::cout << ">>> Incoming Request: " << method << " " << uri << " " << version << "\n";

        // Construct HTML body containing the isolated URI
        std::string body = "<!DOCTYPE html><html><body>"
                           "<h1>HTTP/1.1 Framing Active</h1>"
                           "<p>Parsed Method: <b>" + method + "</b></p>"
                           "<p>Isolated URI: <b>" + uri + "</b></p>"
                           "</body></html>\n";

        // Build compliant HTTP/1.1 response with double CRLF boundary
        std::ostringstream response;
        response << "HTTP/1.1 200 OK\r\n";
        response << "Content-Type: text/html; charset=UTF-8\r\n";
        response << "Content-Length: " << body.size() << "\r\n";
        response << "Connection: close\r\n";
        response << "\r\n"; // Double CRLF (\r\n\r\n) terminates headers
        response << body;

        std::string response_str = response.str();
        send(client_fd, response_str.c_str(), response_str.size(), 0);

        close(client_fd);
    }

    close(server_fd);
    return 0;
}
