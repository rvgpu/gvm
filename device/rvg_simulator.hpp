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
    void TestFact () {
        printf("this is RVGSim\n");
    }

    uint64_t gpu_malloc(uint32_t size);
    void gpu_memcpy(uint64_t dst, const uint64_t src, uint32_t count, bool host_to_device);

    void Run1D(uint32_t count, uint32_t shaderbin, uint64_t args, uint32_t arg_size);
private:
    rvgsim *sim;
    uint64_t pc;
    uint64_t stack_pointer;
    uint64_t gpu_malloc_addr;
};

#endif // __RVG_DEVICE_H___
