/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#include "rvgpu.hpp"

#include "rvg_simulator.hpp"
#include "rvg_physical.hpp"

RVGPU::RVGPU() {
    dev = new RVGSimulator();
}

uint64_t RVGPU::gpu_malloc(uint32_t size) {
    return dev->gpu_malloc(size);
}

void RVGPU::gpu_memcpy(uint64_t dst, const uint64_t src, uint32_t count, bool host_to_device) {
    dev->gpu_memcpy(dst, src, count, host_to_device);
    return;
}

void RVGPU::RunKernel(uint32_t dimx, uint32_t dimy, uint32_t dimz, uint32_t shaderbin, uint64_t args, uint32_t arg_size) {
    dev->RunKernel(dimx, dimy, dimz, shaderbin, args, arg_size);
}
