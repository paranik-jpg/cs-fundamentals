#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore>

std::mutex mtx;
std::counting_semaphore<1> sem(1); // Counting semaphore initialized to 1

int main() {
    std::cout << "[Step 1] Thread A locking both Mutex and Semaphore...\n";
    mtx.lock();       // Thread A acquires mutex ownership
    sem.acquire();    // Thread A decrements semaphore counter (down)

    // Spawn Thread B to attempt cross-thread unlocking[cite: 2]
    std::thread threadB([]() {
        std::cout << "[Thread B] Attempting to release Semaphore...\n";
        sem.release(); // Allowed: Semaphores are pure signaling mechanisms
        std::cout << "[Thread B] Semaphore released successfully!\n";

        std::cout << "[Thread B] Attempting to unlock Mutex owned by Thread A...\n";
        // CRASH: Violates strict thread ownership rules
        mtx.unlock();
        std::cout << "[Thread B] Mutex unlocked successfully!\n";
    });

    threadB.join();
    mtx.unlock();   // Clean up if not already crashed
    return 0;
}
