/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#ifndef __RVG_CUDART_ELF_H__
#define __RVG_CUDART_ELF_H__

namespace cuda {
class ELF {
public:
    ELF(void *elf, int size);

private:
    void *header;
    int  size;
};

}

#endif