/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#include <cstdio>
#include <cstdint>

#include "rvgsim.h"

class rvgmm {
public:
    rvgmm(rvgsim *sim);
    uint64_t get_malloc_addr();
    void set_malloc_addr(uint64_t addr);

    uint64_t lookup_page_table(uint64_t pt_base, uint64_t index);
    void create_page_table(uint64_t va);
    uint64_t find_pa(uint64_t va);
private:
    rvgsim *m_sim;
    uint64_t GPU_MALLOC_ADDR;

    // Page table
    uint64_t PT_BASE;
    uint64_t PT_OFFSET;

    // Physical address
    uint64_t PA_BASE;
    uint64_t PA_OFFSET;
};