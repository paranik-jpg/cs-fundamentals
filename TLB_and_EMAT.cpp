#include <iostream>
#include <cstdint>
#include <iomanip>

//              virtual address
// ┌──────────────┬──────────┬────────────┐
// │    10 bits   │          │            │
// │  higher bits │ 10 bits  │ 12 bits    │
// │              │ index    │ page offset│
// └──────────────┴──────────┴────────────┘
//              ↑ ↑ ↑              ↑
//           Page Number       Page Offset

// Bitmask and shift definitions for 32-bit architecture with 4KB pages
constexpr uint32_t OFFSET_BITS = 12;
constexpr uint32_t PTI_BITS    = 10;
constexpr uint32_t PDI_BITS    = 10;

constexpr uint32_t OFFSET_MASK = 0xFFF;         // Lowest 12 bits
constexpr uint32_t PTI_MASK    = 0x3FF;         // 10 bits
constexpr uint32_t PDI_MASK    = 0x3FF;         // 10 bits

struct AddressDecomposition {
    uint32_t pdi;
    uint32_t pti;
    uint32_t offset;
};

AddressDecomposition decompose(uint32_t virtual_address) {
    AddressDecomposition addr;

    // Keep only the bottom 12 bits
    addr.offset = virtual_address & OFFSET_MASK;

    // Shift by 12 bits and then keep the next 10 bits
    addr.pti    = (virtual_address >> OFFSET_BITS) & PTI_MASK;

    // Shift by (12 + 10) bits and then keep thr top 10 bits
    addr.pdi    = (virtual_address >> (OFFSET_BITS + PTI_BITS)) & PDI_MASK;

    return addr;
}

uint32_t translate(uint32_t virtual_address, uint32_t frame_number) {
    uint32_t offset = virtual_address & OFFSET_MASK;
    // Physical Address = (Frame Number << 12) | Offset

    // Returns (frame_number << 12) | offset

    // Looks like this
    // ┌───────────────┬────────────┐
    // │ frame number  │   offset   │
    // └───────────────┴────────────┘
    return (frame_number << OFFSET_BITS) | offset;
}

int main() {
    // Example Virtual Address: 0x12345678
    uint32_t v_addr = 0x12345678;
    auto decomp = decompose(v_addr);

    std::cout << std::hex << std::uppercase;
    std::cout << "Virtual Address   : 0x" << v_addr << "\n";
    std::cout << "Page Directory Idx: 0x" << decomp.pdi << " (Decimal: " << std::dec << decomp.pdi << ")\n";
    std::cout << "Page Table Index  : 0x" << std::hex << decomp.pti << " (Decimal: " << std::dec << decomp.pti << ")\n";
    std::cout << "Page Offset       : 0x" << std::hex << decomp.offset << " (Decimal: " << std::dec << decomp.offset << ")\n";

    // Simulate looking up page table and finding the page mapped to Frame 0x00ABC
    uint32_t mock_frame = 0x00ABC;
    uint32_t p_addr = translate(v_addr, mock_frame);
    std::cout << "Physical Address  : 0x" << std::hex << p_addr << "\n";

    return 0;
}

// EMAT = t_tlb + m + (1 - h) * (k * m)

// Key Takeaway (EMAT): Every memory access pays the baseline cost of searching the TLB (t_tlb)
// plus fetching the final data byte (m).

// On a miss, you pay an extra penalty of k * m to traverse each page table level in RAM.
