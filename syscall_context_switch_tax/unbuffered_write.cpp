#include <fcntl.h>    // open, O_WRONLY, O_CREAT, O_TRUNC
#include <unistd.h>   // write, close
#include <iostream>

int main() {
    // Open or create file with write-only permissions (0644)
    int fd = open("unbuffered_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    // Direct, unbuffered system call invocation
    for (int i = 0; i < 100000; ++i) {
        write(fd, "A", 1); // Triggers a User -> Kernel mode switch on every iteration
    }

    close(fd); // Release the file descriptor
    return 0;
}
