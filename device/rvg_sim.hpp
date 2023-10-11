/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#ifndef __RVG_SIM_H__
#define __RVG_SIM_H__

#include <cstdio>
#include <cstdint>

#include "rvgsim.h"

#include "rvg_device.hpp"

class RVGSim: public RVGDevice {
public:
    RVGSim();
    void TestFact () {
        printf("this is RVGSim\n");
    }

    uint64_t gpu_malloc(uint32_t size);
    void gpu_memcpy(uint64_t dst, const uint64_t src, uint32_t count, bool host_to_device);

private:
    rvgsim *sim;
    uint64_t pc;
    uint64_t stack_pointer;
    uint64_t gpu_malloc_addr;
};

#endif // __RVG_DEVICE_H___
