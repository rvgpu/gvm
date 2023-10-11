/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#include <cstdio>

#include "fat_binary.hpp"

#include "cuda_runtime.hpp"

using namespace cuda;

Runtime::Runtime() {
    rvg = new RVGPU();
}

void ** Runtime::RegisterFatBinary(void *fatCubin) {
    fatbin = new FatBinary(fatCubin);

    return NULL;
}
