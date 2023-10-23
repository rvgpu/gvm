/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#include "rvg_device.hpp"
#include "command_stream.h"

#define SM_NUM                      8
#define SM_STACK_SIZE               (16 * 0x1000)

RVGDevice::RVGDevice() {
}

RVGDevice::~RVGDevice() {
}

void RVGDevice::RunKernel(uint32_t dimx, uint32_t dimy, uint32_t dimz, uint32_t shaderbin, uint64_t args, uint32_t arg_size) {
    uint64_t stack_pointer;
    stack_pointer = gpu_malloc(SM_STACK_SIZE * SM_NUM + 0x1000);
    stack_pointer += 0x1000;
    rvgpu_command cmd;
    cmd.dim = {.x=dimx, .y=dimy, .z=dimz};
    cmd.program.pointer = shaderbin;
    cmd.program.stack_pointer = stack_pointer;
    cmd.program.argsize = arg_size;
    for (uint32_t i=0; i<arg_size; i++) {
        cmd.program.args[i] = ((uint64_t *)args)[i];
    }

    uint64_t cmd_addr = gpu_malloc(sizeof(rvgpu_command));
    gpu_memcpy(cmd_addr, uint64_t(&cmd), sizeof(rvgpu_command), true);

    SubmitJobs(cmd_addr);
}
