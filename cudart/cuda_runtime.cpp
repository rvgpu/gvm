/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#include <cstdio>

#include "cuda_fatbinary.hpp"
#include "cuda_runtime.hpp"

using namespace cuda;

Runtime::Runtime() {
    rvg = new RVGPU();
}

void ** Runtime::RegisterFatBinary(void *fatCubin) {
    FatBinary *fatbin = new FatBinary(fatCubin);

    return (void **)fatbin;
}

void Runtime::RegisterFunction(void **fatCubinHandle, char *deviceFun) {
    FatBinary *fatbin = static_cast<FatBinary *>((void *)fatCubinHandle);

    uint64_t funbin = fatbin->GetFunctionBin(deviceFun);
    uint32_t size = fatbin->GetFunctionBinSize(deviceFun);

    printf("%ld\n", funbin);
    printf("%d\n", size);
}

uint64_t Runtime::Malloc(uint32_t size) {
    return rvg->gpu_malloc(size);
}

void Runtime::Memcpy(uint64_t dst, const uint64_t src, uint32_t count, bool host_to_device) {
    rvg->gpu_memcpy(dst, src, count, host_to_device);
    return;
}
