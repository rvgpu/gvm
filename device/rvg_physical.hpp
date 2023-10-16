/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#ifndef __RVG_PHY_H__
#define __RVG_PHY_H__

#include <cstdio>
#include <cstdint>

#include "rvg_device.hpp"

class RVGPhy: public RVGDevice {
public:
    RVGPhy() {}
    void TestFact() {
        printf("this is RVGPhy\n");
    }

private:
    
};

#endif // __RVG_PHY_H___
