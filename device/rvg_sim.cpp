/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#include <cstdio>
#include <cstdint>

#include "rvg_sim.hpp"

#define SM_NUM                      8
#define SM_STACK_SIZE               (16 * 0x1000)

RVGSim::RVGSim() {
    sim = new rvgsim();
    gpu_malloc_addr = 0;
    stack_pointer = gpu_malloc(SM_STACK_SIZE * SM_NUM + 0x1000);
    stack_pointer += 0x1000;
}

uint64_t RVGSim::gpu_malloc(uint32_t size) {
    printf("### RVGSim::gpu_malloc\n");
    printf("size = %u\n", size);

    uint64_t addr = gpu_malloc_addr;
    gpu_malloc_addr += size;
    return addr;
}

void RVGSim::gpu_memcpy(uint64_t dst, const uint64_t src, uint32_t count, bool host_to_device) {
    printf("### RVGSim::gpu_memcpy\n");
    printf("host_to_device = %d\n", host_to_device);

    // Host to device data
    if (host_to_device) {
        float *src_float = (float *)src;
        for (uint32_t n = 0; n < count / sizeof(float); n++) {
            printf("src_float[%u] = %f\n", n, *(src_float + n));
        }
    }

    if (host_to_device) {
        uint8_t *addr = (uint8_t *)src;
        for (uint32_t i = 0; i < count; i++) {
            sim->write_vram(dst + i, addr[i], 1);
        }
    } else {
        uint8_t *addr = (uint8_t *)dst;
        for (uint32_t i = 0; i < count; i++) {
            addr[i] = sim->read_vram(src + i, 1);
        }
    }

    // Device to host data
    if (!host_to_device) {
        float *dst_float = (float *)dst;
        for (uint32_t n = 0; n < count / sizeof(float); n++) {
            printf("dst_float[%u] = %f\n", n, *(dst_float + n));
        }
    }

    return;
}
