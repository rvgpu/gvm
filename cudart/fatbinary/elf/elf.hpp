/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#ifndef __RVG_CUDART_ELF_H__
#define __RVG_CUDART_ELF_H__

#include "elf.h"
#include "section.hpp"

namespace cuda {

typedef struct {
    char        *name;
    uint64_t    binary;
    uint32_t    binsize;
} DeviceFunc;

class ELF {
public:
    ELF(void *elf, int size);
    bool HasFunction(char *name);
    bool GetFunction(char *fname, uint64_t &bin, uint32_t &size);

private:
    bool isRVGPU(void *header);
    bool MagicIsELF(void *header);

    // 打印输出 ELF Header的信息
    void HeaderInfo(void *header);

    section *m_section;
};

}

#endif