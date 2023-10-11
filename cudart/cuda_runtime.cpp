/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#include <cstdio>

#include "fat_binary.hpp"

#include "cuda_runtime.hpp"

using namespace cuda;

Runtime::Runtime() {
    rvg = new RVGPU();
}

void ** Runtime::RegisterFatBinary(void *fatCubin) {
    fatbin = new FatBinary(fatCubin);

    return NULL;
}

uint64_t Runtime::Malloc(uint32_t size) {
    return rvg->gpu_malloc(size);
}

void Runtime::Memcpy(uint64_t dst, const uint64_t src, uint32_t count, bool host_to_device) {
    rvg->gpu_memcpy(dst, src, count, host_to_device);
    return;
}
