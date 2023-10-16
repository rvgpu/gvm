/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#include <vector>
#include <map>
#include "cuda_runtime_api.h"

#include "cuda_fatbinary.hpp"
#include "rvgpu.hpp"

namespace cuda {

class Runtime {
public:
    Runtime();

    void ** RegisterFatBinary(void *fatCubin);
    void RegisterFunction(void **fatCubinHandle, const char *hostFun, char *deviceFun);
    
    uint64_t Malloc(uint32_t size);
    void Memcpy(uint64_t dst, const uint64_t src, uint32_t count, bool host_to_device);


    void LaunchKerne(const void *hostFun, dim3 gridDim, dim3 blockDim, void **args);
private:
    RVGPU *rvg;

    std::map<uint64_t, DeviceFunc *> stored_func;
};

}
