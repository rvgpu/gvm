/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#ifndef __RVGPU_H__
#define __RVGPU_H__

#include <cstdint>

class RVGDevice;
class RVGPU {
public:
    RVGPU();

    uint64_t gpu_malloc(uint32_t size);
    void gpu_memcpy(uint64_t dst, const uint64_t src, uint32_t count, bool host_to_device);

    void Run1D(uint32_t count, uint32_t shaderbin, uint64_t args, uint32_t arg_size);

private:
    RVGDevice *dev;
};

#endif // __RVGPU_H__
