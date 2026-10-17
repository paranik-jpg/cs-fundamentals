#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <cstdlib>

int main() {
    pid_t pid = fork(); // Clone parent process

    if (pid < 0) {
        std::cerr << "Fork failed!\n";
        return 1;
    }

    if (pid == 0) {
        // Child Process: exits immediately into zombie state
        std::cout << "[Child] PID: " << getpid() << " exiting now...\n";
        exit(0);
    } else {
        // Parent Process: runs indefinitely without calling wait()
        std::cout << "[Parent] PID: " << getpid() << " spawned Child PID: " << pid << "\n";
        std::cout << "[Parent] Looping forever without calling wait()...\n";
        while (true) {
            sleep(1);
        }
    }

    return 0;
}
