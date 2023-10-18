/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#ifndef __RVG_SIM_H__
#define __RVG_SIM_H__

#include <cstdio>
#include <cstdint>

#include "rvgsim.h"

#include "rvg_device.hpp"

class RVGSimulator: public RVGDevice {
public:
    RVGSimulator();

    uint64_t gpu_malloc(uint32_t size);
    void gpu_memcpy(uint64_t dst, const uint64_t src, uint32_t count, bool host_to_device);

    void Run1D(uint32_t count, uint32_t shaderbin, uint64_t args, uint32_t arg_size);
private:
    rvgsim *sim;
    uint64_t pc;
    uint64_t stack_pointer;
    uint64_t GPU_MALLOC_ADDR;

    // Page table
    uint64_t PT_BASE;
    uint64_t PT_OFFSET;

    // Physical address
    uint64_t PA_BASE;
    uint64_t PA_OFFSET;

    uint64_t lookup_page_table(uint64_t pt_base, uint64_t index);
    void create_page_table(uint64_t va);
    uint64_t find_pa(uint64_t va);
};

#endif // __RVG_DEVICE_H___
