#include <iostream>
#include <vector>

const int P = 5; // Number of processes
const int R = 3; // Number of resource types (A, B, C)

void calculateRemainingNeed(int need[P][R], int max[P][R], int alloc[P][R]) {
    for (int i = 0; i < P; ++i) {
        for (int j = 0; j < R; ++j) {
            need[i][j] = max[i][j] - alloc[i][j]; // Remaining Need = Max - Allocation
        }
    }
}

bool isSafeState(int processes[], int avail[], int max[][R], int alloc[][R]) {
    int need[P][R];
    calculateRemainingNeed(need, max, alloc);

    bool finish[P] = {false};
    int safeSeq[P];
    int work[R];

    for (int i = 0; i < R; ++i) {
        work[i] = avail[i];
    }

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; ++p) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < R; ++j) {
                    if (need[p][j] > work[j]) {
                        break; // Process cannot execute with current available resources
                    }
                }

                // If all resource needs can be satisfied
                if (j == R) {
                    for (int k = 0; k < R; ++k) {
                        work[k] += alloc[p][k]; // Release allocated resources back to pool
                    }
                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            std::cout << "System is in an UNSAFE state (Deadlock imminent)!\n";
            return false;
        }
    }

    std::cout << "System is in a SAFE state.\nSafe Sequence: ";
    for (int i = 0; i < P; ++i) {
        std::cout << "P" << safeSeq[i] << (i == P - 1 ? "" : " -> ");
    }
    std::cout << "\n";
    return true;
}

int main() {
    int processes[] = {0, 1, 2, 3, 4};

    // Current available instances calculated as: Total - Sum(Allocated)
    // Total: [10, 5, 7], Allocated Sum: [7, 2, 5] -> Available: [3, 3, 2]
    int avail[] = {3, 3, 2};

    int max[][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int alloc[][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    isSafeState(processes, avail, max, alloc);
    return 0;
}
