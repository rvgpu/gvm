#pragma once

#include <map>
#include <string>
#include <cstdint>
#include <elf.h>

namespace cuda {

class section {
public:
    section(void *elf);
    
    bool GetFunction(char *fname, uint64_t &bin, uint32_t &size);
private:
    Elf64_Sym *FindSymbol(char *name);
    Elf64_Shdr *GetSection(std::string str);

    std::string SymbolNameStr(uint32_t idx);
    std::string SHNameStr(uint32_t idx);
    std::string TypeStr(uint32_t type);
    void HeaderInfo();

    // ELF base address,所有的偏移是基于elf的baseaddres计算的
    uint8_t *m_baseaddr;

    // Section Header的信息
    Elf64_Shdr *m_shtab;
    uint32_t m_shnum;
    std::map<std::string, Elf64_Shdr *> m_shname_id;

    // Section Header String Table
    char *m_shstrtab;
    // String Table

    // Symbol Table
    Elf64_Sym *m_symtab;
    uint32_t m_symtab_num;

    char *m_strtab;
};

} // namespace cuda