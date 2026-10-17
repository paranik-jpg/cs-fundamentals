#include <fstream>
#include <iostream>

int main() {
    std::ofstream outFile("buffered_output.txt"); // Manages an internal user-space buffer
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    for (int i = 0; i < 100000; ++i) {
        outFile << "A"; // Aggregates characters in memory; avoids immediate syscalls[cite: 1, 2]
    }

    outFile.close(); // Flushes the remaining buffer to disk via a final write() syscall[cite: 1, 2]
    return 0;
}
