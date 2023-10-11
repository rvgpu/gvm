/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#ifndef __RVG_CUDART_ELF_H__
#define __RVG_CUDART_ELF_H__

#include "elf.h"

namespace cuda {
class ELF {
public:
    ELF(void *elf, int size);

private:
    bool CheckMagic(void *header);

    // function to print elf info
    void HeaderInfo(void *header);

    // store string table and symbol table
    Elf64_Sym   *symbol_table;
    char        *string_table;
};

}

#endif