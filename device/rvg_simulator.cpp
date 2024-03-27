/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#include <cstdio>
#include <cstdint>

#include "command_stream.h"
#include "rvg_simulator.hpp"

#define SM_NUM                      8
#define SM_STACK_SIZE               (16 * 0x1000)

RVGSimulator::RVGSimulator() {
    sim = new rvgsim();
    mm = new rvgmm(sim);

    printf("This is RVG Simulator\n");
}

uint64_t RVGSimulator::gpu_malloc(uint32_t size) {
    uint64_t addr = mm->get_malloc_addr();

    // Create page table
    uint32_t pt_count = ((addr + size) / 0x1000) - (addr / 0x1000) + 1;
    for (uint32_t i = 0; i < pt_count; i++) {
        mm->create_page_table(addr + i * 0x1000);
    }

    mm->set_malloc_addr(addr + size);

    return addr;
}

void RVGSimulator::gpu_memcpy(uint64_t dst, const uint64_t src, uint32_t count, bool host_to_device) {
    // Find physical address
    if (host_to_device) {
        uint8_t *addr = (uint8_t *)src;
        for (uint32_t i = 0; i < count; i++) {
            uint64_t pa = mm->find_pa(dst + i);
            sim->write_vram(pa, addr[i], 1);
        }
    } else {
        uint8_t *addr = (uint8_t *)dst;
        for (uint32_t i = 0; i < count; i++) {
            uint64_t pa = mm->find_pa(src + i);
            addr[i] = sim->read_vram(pa, 1);
        }
    }
}

void RVGSimulator::SubmitJobs(uint64_t cmds) {
    sim->write_mmio(0x1000, cmds);
    sim->write_mmio(0x1010, mm->get_page_table_base());
    sim->write_mmio(0x1008, 1);
}
