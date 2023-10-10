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

private:
    RVGDevice *dev;
};

#endif // __RVGPU_H__
