#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <list>
#include <unordered_map>

int run_fifo(const std::vector<int>& pages, int capacity) {
    std::unordered_set<int> memory_set; // Fast lookup for current resident pages
    std::queue<int> fifo_queue;         // Tracks arrival order for FIFO eviction
    int page_faults = 0;
    int hits = 0;

    std::cout << "\n--- FIFO Simulation (Capacity: " << capacity << " frames) ---\n";

    for (int page : pages) {
        // Cache Hit: Page is already in memory
        if (memory_set.find(page) != memory_set.end()) {
            hits++;
            std::cout << "Page " << page << " -> HIT\n";
            continue;
        }

        // Cache Miss / Page Fault
        page_faults++;

        // If memory is saturated, evict the oldest page at the front of the queue
        if (memory_set.size() == capacity) {
            int oldest = fifo_queue.front();
            fifo_queue.pop();
            memory_set.erase(oldest);
            std::cout << "Page " << page << " -> FAULT (Evicted " << oldest << ")\n";
        } else {
            std::cout << "Page " << page << " -> FAULT (Allocated free frame)\n";
        }

        // Insert the incoming page into memory and queue
        memory_set.insert(page);
        fifo_queue.push(page);
    }

    std::cout << "Total Faults: " << page_faults << " | Total Hits: " << hits << "\n";
    return page_faults;
}

int run_lru(const std::vector<int>& pages, int capacity) {
    std::list<int> lru_list; // Front = MRU, Back = LRU
    std::unordered_map<int, std::list<int>::iterator> page_map;
    int page_faults = 0;
    int hits = 0;

    std::cout << "\n--- LRU Simulation (Capacity: " << capacity << " frames) ---\n";

    for (int page : pages) {
        auto it = page_map.find(page);

        // Cache Hit
        if (it != page_map.end()) {
            hits++;
            // Splice moves the existing node directly to the front in O(1)
            lru_list.splice(lru_list.begin(), lru_list, it->second);
            std::cout << "Page " << page << " -> HIT (Promoted to MRU)\n";
            continue;
        }

        // Cache Miss / Page Fault
        page_faults++;

        // Evict LRU element if frame capacity is exhausted
        if (page_map.size() == capacity) {
            int lru_page = lru_list.back();
            lru_list.pop_back();
            page_map.erase(lru_page);
            std::cout << "Page " << page << " -> FAULT (Evicted LRU: " << lru_page << ")\n";
        } else {
            std::cout << "Page " << page << " -> FAULT (Allocated free frame)\n";
        }

        // Insert new page as Most Recently Used
        lru_list.push_front(page);
        page_map[page] = lru_list.begin();
    }

    std::cout << "Total Faults: " << page_faults << " | Total Hits: " << hits << "\n";
    return page_faults;
}

int main() {
    // Task 12 Reference String: 1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5
    std::vector<int> pages = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};

    // Run with 3 frames (yields 9 faults)
    run_fifo(pages, 3);

    // Run with 4 frames (yields 10 faults -> Belady's Anomaly)
    run_fifo(pages, 4);

    // Test with 3 frames
    run_lru(pages, 3);

    // Test with 4 frames
    run_lru(pages, 4);

    return 0;
}
