#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mtxA;
std::mutex mtxB;

void thread1_work() {
    std::cout << "[Thread 1] Acquiring Mutex A...\n";
    mtxA.lock(); //
    std::cout << "[Thread 1] Acquired Mutex A! Simulating work...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    std::cout << "[Thread 1] Attempting to acquire Mutex B...\n";
    mtxB.lock(); // Blocks: Mutex B is held by Thread 2
    std::cout << "[Thread 1] Acquired Mutex B!\n";

    mtxB.unlock();
    mtxA.unlock();
}

void thread2_work() {
    std::cout << "[Thread 2] Acquiring Mutex B...\n";
    mtxB.lock();
    std::cout << "[Thread 2] Acquired Mutex B! Simulating work...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    std::cout << "[Thread 2] Attempting to acquire Mutex A...\n";
    mtxA.lock(); // Blocks: Mutex A is held by Thread 1
    std::cout << "[Thread 2] Acquired Mutex A!\n";

    mtxA.unlock();
    mtxB.unlock();
}

int main() {
    std::thread t1(thread1_work);
    std::thread t2(thread2_work);

    t1.join();
    t2.join();
    return 0;
}
