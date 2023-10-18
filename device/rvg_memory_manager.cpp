/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#include <cstdio>
#include <cstdint>

#include "rvg_memory_manager.hpp"

#define _BITS(bits, pos, width) (((bits) >> (pos)) & ((1ULL << (width)) - 1ULL))

rvgmm::rvgmm(rvgsim *sim) {
    m_sim = sim;
    GPU_MALLOC_ADDR = 0x10000;

    // Page table
    PT_BASE = 0x00100000;
    PT_OFFSET = 0x00000000;
    PT_OFFSET += 0x1000;

    // Physical address
    PA_BASE = 0x10000000;
    PA_OFFSET = 0x00000000;
}

uint64_t rvgmm::get_malloc_addr() {
    return GPU_MALLOC_ADDR;
}

void rvgmm::set_malloc_addr(uint64_t addr) {
    GPU_MALLOC_ADDR = addr;
}

uint64_t rvgmm::lookup_page_table(uint64_t pt_base, uint64_t index) {
    uint64_t result;
    uint64_t pt_entry = m_sim->read_vram(pt_base + index * 8, 8);

    // Page table entry, PT_BASE + PT_OFFSET
    if (pt_entry == 0) {
        m_sim->write_vram(pt_base + index * 8, PT_BASE + PT_OFFSET, 8);
        result = PT_BASE + PT_OFFSET;
        PT_OFFSET += 0x1000;
    } else {
        result = pt_entry;
    }

    return result;
}

void rvgmm::create_page_table(uint64_t va) {
    uint64_t level1 = lookup_page_table(PT_BASE, _BITS(va, 39, 9));
    uint64_t level2 = lookup_page_table(level1, _BITS(va, 30, 9));
    uint64_t level3 = lookup_page_table(level2, _BITS(va, 21, 9));

    uint64_t level3_index = _BITS(va, 12, 9);
    uint64_t level3_entry = m_sim->read_vram(level3 + level3_index * 8, 8);

    // Page table entry, PA_BASE + PA_OFFSET
    if (level3_entry == 0) {
        m_sim->write_vram(level3 + level3_index * 8, PA_BASE + PA_OFFSET, 8);
        PA_OFFSET += 0x1000;
    } else {
        // Do nothing
    }
}

uint64_t rvgmm::find_pa(uint64_t va) {
    uint64_t level1 = lookup_page_table(PT_BASE, _BITS(va, 39, 9));
    uint64_t level2 = lookup_page_table(level1, _BITS(va, 30, 9));
    uint64_t level3 = lookup_page_table(level2, _BITS(va, 21, 9));

    uint64_t level3_index = _BITS(va, 12, 9);
    uint64_t level3_entry = m_sim->read_vram(level3 + level3_index * 8, 8);

    if (level3_entry == 0) {
        printf("Page not found\n");
        return 0;
    } else {
        return level3_entry + _BITS(va, 0, 12);
    }
}
