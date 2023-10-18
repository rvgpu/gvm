/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#include <cstdio>
#include <cstdint>

#include "command_stream.h"
#include "rvg_simulator.hpp"

#define SM_NUM                      8
#define SM_STACK_SIZE               (16 * 0x1000)

#define _BITS(bits, pos, width) (((bits) >> (pos)) & ((1ULL << (width)) - 1ULL))

RVGSimulator::RVGSimulator() {
    sim = new rvgsim();
    GPU_MALLOC_ADDR = 0x10000;

    // Page table
    PT_BASE = 0x00100000;
    PT_OFFSET = 0x00000000;
    PT_OFFSET += 0x1000;

    // Physical address
    PA_BASE = 0x10000000;
    PA_OFFSET = 0x00000000;

    stack_pointer = gpu_malloc(SM_STACK_SIZE * SM_NUM + 0x1000);
    stack_pointer += 0x1000;

    printf("This is RVG Simulator\n");
}

uint64_t RVGSimulator::lookup_page_table(uint64_t pt_base, uint64_t index) {
    uint64_t result;
    uint64_t pt_entry = sim->read_vram(pt_base + index * 8, 8);

    // Page table entry, PT_BASE + PT_OFFSET
    if (pt_entry == 0) {
        sim->write_vram(pt_base + index * 8, PT_BASE + PT_OFFSET, 8);
        result = PT_BASE + PT_OFFSET;
        PT_OFFSET += 0x1000;
    } else {
        result = pt_entry;
    }

    return result;
}

void RVGSimulator::create_page_table(uint64_t va) {
    uint64_t level1 = lookup_page_table(PT_BASE, _BITS(va, 39, 9));
    uint64_t level2 = lookup_page_table(level1, _BITS(va, 30, 9));
    uint64_t level3 = lookup_page_table(level2, _BITS(va, 21, 9));

    uint64_t level3_index = _BITS(va, 12, 9);
    uint64_t level3_entry = sim->read_vram(level3 + level3_index * 8, 8);

    // Page table entry, PA_BASE + PA_OFFSET
    if (level3_entry == 0) {
        sim->write_vram(level3 + level3_index * 8, PA_BASE + PA_OFFSET, 8);
        PA_OFFSET += 0x1000;
    } else {
        // Do nothing
    }
}

uint64_t RVGSimulator::find_pa(uint64_t va) {
    uint64_t level1 = lookup_page_table(PT_BASE, _BITS(va, 39, 9));
    uint64_t level2 = lookup_page_table(level1, _BITS(va, 30, 9));
    uint64_t level3 = lookup_page_table(level2, _BITS(va, 21, 9));

    uint64_t level3_index = _BITS(va, 12, 9);
    uint64_t level3_entry = sim->read_vram(level3 + level3_index * 8, 8);

    if (level3_entry == 0) {
        printf("Page not found\n");
        return 0;
    } else {
        return level3_entry + _BITS(va, 0, 12);
    }
}

uint64_t RVGSimulator::gpu_malloc(uint32_t size) {
    uint64_t addr = GPU_MALLOC_ADDR;

    // Create page table
    uint32_t pt_count = ((size - 1) / 0x1000) + 1;
    for (uint32_t i = 0; i < pt_count; i++) {
        create_page_table(addr + i * 0x1000);
    }

    GPU_MALLOC_ADDR += size;

    return addr;
}

void RVGSimulator::gpu_memcpy(uint64_t dst, const uint64_t src, uint32_t count, bool host_to_device) {
    // Find physical address
    if (host_to_device) {
        uint8_t *addr = (uint8_t *)src;
        for (uint32_t i = 0; i < count; i++) {
            uint64_t pa = find_pa(dst + i);
            sim->write_vram(pa, addr[i], 1);
        }
    } else {
        uint8_t *addr = (uint8_t *)dst;
        for (uint32_t i = 0; i < count; i++) {
            uint64_t pa = find_pa(src + i);
            addr[i] = sim->read_vram(pa, 1);
        }
    }
}

void RVGSimulator::Run1D(uint32_t count, uint32_t shaderbin, uint64_t args, uint32_t arg_size) {
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
