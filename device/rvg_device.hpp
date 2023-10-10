/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#ifndef __RVG_DEVICE_H__
#define __RVG_DEVICE_H__

#include <cstdint>

typedef enum RVGDeviceType {
    CSimulator,
    PhysicalDevice,
} RVGDeviceType;

class RVGDevice {
public:
    RVGDevice () {}
    ~RVGDevice() {};

    virtual void TestFact() = 0;

private:
    
};

#endif // __RVG_DEVICE_H___
