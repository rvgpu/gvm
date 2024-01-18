/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#ifndef __RVG_FATBINARY_H__
#define __RVG_FATBINARY_H__

#include <stdint.h>
#include <vector>

#include "utils/macro.hpp"

#include "clang_offload_bundle.hpp"

namespace cuda {

class FatBinary {
public:
    FatBinary(void *fatCubin);
    DeviceFunc *GetDeviceFunc(char *funcname);

private:
    // Structure of cuda_fatbin
    typedef struct {
        int32_t     magic;
        int32_t     version;
        int64_t     pCOB;
        int64_t     dummy1;
    } Wrapper ALIGNED(8);

    Wrapper *m_wrapper;
    ClangOffloadBundle *m_bundle;
};

}

#endif // __RVG_FATBINARY_H__
