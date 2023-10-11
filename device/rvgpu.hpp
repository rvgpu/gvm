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

private:
    RVGDevice *dev;
};

#endif // __RVGPU_H__
