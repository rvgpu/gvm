/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#ifndef __RVG_DEVICE_H__
#define __RVG_DEVICE_H__

#include <cstdint>

typedef enum class RVGDeviceType {
    CSimulator,
    PhysicalDevice,
} RVGDeviceType;

class RVGDevice {
public:
    RVGDevice () {};
    ~RVGDevice() {};

    virtual uint64_t gpu_malloc(uint32_t size) = 0;
    virtual void gpu_memcpy(uint64_t dst, const uint64_t src, uint32_t count, bool host_to_device) = 0;

    virtual void RunKernel(uint32_t dimx, uint32_t dimy, uint32_t dimz, uint32_t shaderbin, uint64_t args, uint32_t arg_size) = 0;

private:
    
};

#endif // __RVG_DEVICE_H___
