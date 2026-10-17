#include <iostream>
#include <vector>
#include <thread>

// Shared resource accessed concurrently
int shared_counter = 0;

void worker() {
    for (int i = 0; i < 10000; ++i) {
        // Non-atomic operation: Read -> Modify -> Write
        shared_counter++;
    }
}

int main() {
    std::vector<std::thread> threads;

    // Spawning 10 user-level threads mapping directly to kernel execution contexts
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(worker);
    }

    // Await termination of all worker threads
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Expected count: 100000\n";
    std::cout << "Actual count  : " << shared_counter << "\n";

    return 0;
}
