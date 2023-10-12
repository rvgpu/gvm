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

    stored_func = fatbin->GetDeviceFunc(deviceFun);
}

uint64_t Runtime::Malloc(uint32_t size) {
    return rvg->gpu_malloc(size);
}

void Runtime::Memcpy(uint64_t dst, const uint64_t src, uint32_t count, bool host_to_device) {
    rvg->gpu_memcpy(dst, src, count, host_to_device);
    return;
}

void Runtime::LaunchKerne(const void *hostFun, dim3 gridDim, dim3 blockDim, void **args) {
    uint64_t funcaddr = rvg->gpu_malloc(stored_func->binsize);
    rvg->gpu_memcpy(funcaddr, stored_func->binary, stored_func->binsize, true);

    printf("Run Kernel\n");
    uint64_t params[3];
    params[0] = *((uint32_t *)args[0]);
    params[1] = *((uint64_t *)args[1]);
    params[2] = *((uint64_t *)args[2]);

    rvg->Run1D(gridDim.z, funcaddr, uint64_t(params), 3);
}
