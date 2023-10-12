/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#include <cstdio>
#include <cstdint>

#include "command_stream.h"
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
    uint64_t addr = gpu_malloc_addr;
    gpu_malloc_addr += size;
    return addr;
}

void RVGSim::gpu_memcpy(uint64_t dst, const uint64_t src, uint32_t count, bool host_to_device) {
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
    return;
}


void RVGSim::Run1D(uint32_t count, uint32_t shaderbin, uint64_t args, uint32_t arg_size) {
    rvgpu_command cmd;
    cmd.type = RVGPU_COMMAND_TYPE_1D;
    cmd.range = {.x=count, .y=0, .z=0};
    cmd.shader.pointer = shaderbin;
    cmd.shader.stack_pointer = stack_pointer;
    cmd.shader.argsize = arg_size;
    for (uint32_t i=0; i<arg_size; i++) {
        cmd.shader.args[i] = ((uint64_t *)args)[i];
    }

    sim->run_with_vram(uint64_t(&cmd));
}
