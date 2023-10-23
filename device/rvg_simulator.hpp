/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#ifndef __RVG_SIM_H__
#define __RVG_SIM_H__

#include <cstdio>
#include <cstdint>

#include "rvgsim.h"

#include "rvg_device.hpp"
#include "rvg_memory_manager.hpp"

class RVGSimulator: public RVGDevice {
public:
    RVGSimulator();

    uint64_t gpu_malloc(uint32_t size);
    void gpu_memcpy(uint64_t dst, const uint64_t src, uint32_t count, bool host_to_device);
    void SubmitJobs(uint64_t cmds);
private:
    rvgsim *sim;
    rvgmm *mm;
    uint64_t pc;
};

#endif // __RVG_DEVICE_H___
