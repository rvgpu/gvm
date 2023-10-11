/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#include <vector>

#include "fat_binary.hpp"
#include "rvgpu.hpp"

namespace cuda {

class Runtime {
public:
    Runtime();

    void ** RegisterFatBinary(void *fatCubin);
    
    uint64_t Malloc(uint32_t size);
    void Memcpy(uint64_t dst, const uint64_t src, uint32_t count, bool host_to_device);

private:
    RVGPU *rvg;
    FatBinary *fatbin;
};

}
