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
    void *FindSymbol(char *name);
    bool GetFunction(void *psym, uint64_t &bin, uint32_t &size);

private:
    bool isRVGPU(void *header);
    bool MagicIsELF(void *header);

    // function to print elf info
    void HeaderInfo(void *header);
    void SectionHeaderInfo(void *header);
    char *SymbolName(uint32_t id);

    section *m_section;
    // ELF header
    Elf64_Ehdr *header;

    // Section Header
    Elf64_Shdr *section_header;

    // store string table and symbol table
    Elf64_Shdr  *strtab_section_header;
    char        *string_table;

    Elf64_Shdr  *symtab_section_header;
    Elf64_Sym   *symbol_table;
};

}

#endif