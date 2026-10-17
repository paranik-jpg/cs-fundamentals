#include <iostream>
#include <cstdint>
#include <iomanip>

// System Geometry
constexpr uint64_t BLOCK_SIZE = 128; // 128 Bytes per block
constexpr uint64_t PTR_SIZE   = 8;   // 8 Bytes per address pointer
constexpr uint64_t PTRS_PER_BLOCK = BLOCK_SIZE / PTR_SIZE; // 16 pointers per index block

// UNIX Inode Pointer Allocation
constexpr uint64_t NUM_DIRECT          = 12;
constexpr uint64_t NUM_SINGLE_INDIRECT = 1;
constexpr uint64_t NUM_DOUBLE_INDIRECT = 1;
constexpr uint64_t NUM_TRIPLE_INDIRECT = 1;

struct InodeCapacityMetrics {
    uint64_t direct_blocks;
    uint64_t single_indirect_blocks;
    uint64_t double_indirect_blocks;
    uint64_t triple_indirect_blocks;
    uint64_t total_blocks;
    uint64_t total_bytes;
    double   total_kb;
};

InodeCapacityMetrics calculate_limits() {
    InodeCapacityMetrics m;

    m.direct_blocks          = NUM_DIRECT;
    m.single_indirect_blocks = NUM_SINGLE_INDIRECT * PTRS_PER_BLOCK;
    m.double_indirect_blocks = NUM_DOUBLE_INDIRECT * PTRS_PER_BLOCK * PTRS_PER_BLOCK;
    m.triple_indirect_blocks = NUM_TRIPLE_INDIRECT * PTRS_PER_BLOCK * PTRS_PER_BLOCK * PTRS_PER_BLOCK;

    m.total_blocks = m.direct_blocks + m.single_indirect_blocks +
                     m.double_indirect_blocks + m.triple_indirect_blocks;

    m.total_bytes  = m.total_blocks * BLOCK_SIZE;
    m.total_kb     = static_cast<double>(m.total_bytes) / 1024.0;

    return m;
}

int main() {
    auto metrics = calculate_limits();

    std::cout << "===========================================\n";
    std::cout << "  UNIX INODE CAPACITY AUDIT (128 B BLOCKS) \n";
    std::cout << "===========================================\n";
    std::cout << "Pointers per Block      : " << PTRS_PER_BLOCK << "\n";
    std::cout << "-------------------------------------------\n";
    std::cout << "Direct Blocks           : " << metrics.direct_blocks
              << " (" << metrics.direct_blocks * BLOCK_SIZE << " Bytes)\n";
    std::cout << "Single Indirect Blocks  : " << metrics.single_indirect_blocks
              << " (" << metrics.single_indirect_blocks * BLOCK_SIZE << " Bytes)\n";
    std::cout << "Double Indirect Blocks  : " << metrics.double_indirect_blocks
              << " (" << metrics.double_indirect_blocks * BLOCK_SIZE << " Bytes)\n";
    std::cout << "Triple Indirect Blocks  : " << metrics.triple_indirect_blocks
              << " (" << metrics.triple_indirect_blocks * BLOCK_SIZE << " Bytes)\n";
    std::cout << "-------------------------------------------\n";
    std::cout << "Total Addressable Blocks: " << metrics.total_blocks << "\n";
    std::cout << "Total File Size (Bytes) : " << metrics.total_bytes << " B\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Absolute Max File Size  : " << metrics.total_kb << " KB\n";
    std::cout << "===========================================\n";

    return 0;
}
