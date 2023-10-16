/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#include <cstdio>
#include <cstdlib>

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

void Runtime::RegisterFunction(void **fatCubinHandle, const char *hostFun, char *deviceFun) {
    FatBinary *fatbin = static_cast<FatBinary *>((void *)fatCubinHandle);

    stored_func.insert(std::make_pair<uint64_t, DeviceFunc *>(uint64_t(hostFun), fatbin->GetDeviceFunc(deviceFun)));
}

uint64_t Runtime::Malloc(uint32_t size) {
    return rvg->gpu_malloc(size);
}

void Runtime::Memcpy(uint64_t dst, const uint64_t src, uint32_t count, bool host_to_device) {
    rvg->gpu_memcpy(dst, src, count, host_to_device);
    return;
}

void Runtime::LaunchKerne(const void *hostFun, dim3 gridDim, dim3 blockDim, void **args) {
    DeviceFunc *dev_fun = stored_func[uint64_t(hostFun)];

    uint64_t funcaddr = rvg->gpu_malloc(dev_fun->binsize);
    rvg->gpu_memcpy(funcaddr, dev_fun->binary, dev_fun->binsize, true);

    printf("Run Kernel:\n");
    uint32_t argsize = 3;
    uint64_t *params = (uint64_t *)malloc(sizeof(uint64_t) * argsize);
    for (uint32_t i=0; i<argsize; i++) {
        params[i] = *((uint64_t *)args[i]);
    }

    rvg->Run1D(gridDim.z, funcaddr, uint64_t(params), argsize);
}
