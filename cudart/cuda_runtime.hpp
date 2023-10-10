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
    
private:
    RVGPU *rvg;
};

}
