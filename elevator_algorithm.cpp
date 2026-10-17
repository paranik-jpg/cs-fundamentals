#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

int main() {
    int initial_head = 50;
    int disk_end = 199;
    std::vector<int> requests = {82, 170, 43, 140, 24, 16, 190};

    std::vector<int> left, right;
    for (int r : requests) {
        if (r < initial_head) left.push_back(r);
        else right.push_back(r);
    }

    std::sort(left.begin(), left.end(), std::greater<int>());
    std::sort(right.begin(), right.end());

    int total_movement = 0;
    int current = initial_head;

    std::cout << "SCAN Trajectory:\n" << current;

    // Upward sweep
    for (int r : right) {
        total_movement += std::abs(r - current);
        current = r;
        std::cout << " -> " << current;
    }

    // Touch boundary
    total_movement += std::abs(disk_end - current);
    current = disk_end;
    std::cout << " -> " << current;

    // Downward sweep
    for (int r : left) {
        total_movement += std::abs(r - current);
        current = r;
        std::cout << " -> " << current;
    }

    std::cout << "\n\nTotal Head Movement: " << total_movement << " cylinders\n";
    return 0;
}
