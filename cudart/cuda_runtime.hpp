/*
 * Copyright © 2023 Sietium Semiconductor.
 */
#pragma once

#include <vector>
#include <map>
#include <stack>

#include "fatbinary/fatbinary.hpp"
#include "cuda_runtime_api.h"
#include "rvgpu.hpp"

namespace cuda {

class Runtime {
public:
    Runtime();

    void ** RegisterFatBinary(void *fatCubin);
    void RegisterFunction(void **fatCubinHandle, const char *hostFun, char *deviceFun);
    
    uint64_t Malloc(uint32_t size);
    void Memcpy(uint64_t dst, const uint64_t src, uint32_t count, bool host_to_device);

    uint32_t PushCallConfiguration(dim3 gridDim, dim3 blockDim);
    uint32_t PopCallConfiguration(dim3 *grdiDim, dim3 *blockDim);
    void LaunchKerne(const void *hostFun, dim3 gridDim, dim3 blockDim, void **args);
private:
    typedef struct {
        dim3 grid;
        dim3 block;
    } Dimension;

    RVGPU *rvg;

    std::stack<Dimension> mCallConfig;
    std::map<uint64_t, DeviceFunc *> stored_func;
};

}
