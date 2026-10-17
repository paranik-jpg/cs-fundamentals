#include <iostream>

// 1. Unordered struct (Subject to padding)
struct BadAlignment {
    char c1; // 1 byte
    int i;   // 4 bytes (requires 4-byte alignment boundary)
    char c2; // 1 byte
};

// 2. Greedy alignment (Largest to smallest)
struct GoodAlignment {
    int i;   // 4 bytes
    char c1; // 1 byte
    char c2; // 1 byte
};

int main() {
    std::cout << "--- BAD ALIGNMENT ---\n";
    std::cout << "Total Size: " << sizeof(BadAlignment) << " bytes\n";
    std::cout << "  c1 offset: " << offsetof(BadAlignment, c1) << "\n"; // offsetof() lets you find the exact byte offset of any member variable from the very beginning of the structure
    std::cout << "  i  offset: " << offsetof(BadAlignment, i) << "\n";
    std::cout << "  c2 offset: " << offsetof(BadAlignment, c2) << "\n\n";

    std::cout << "--- GREEDY ALIGNMENT ---\n";
    std::cout << "Total Size: " << sizeof(GoodAlignment) << " bytes\n";
    std::cout << "  i  offset: " << offsetof(GoodAlignment, i) << "\n";
    std::cout << "  c1 offset: " << offsetof(GoodAlignment, c1) << "\n";
    std::cout << "  c2 offset: " << offsetof(GoodAlignment, c2) << "\n";

    return 0;
}
