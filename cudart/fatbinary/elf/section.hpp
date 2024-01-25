#pragma once

#include <map>
#include <string>
#include <cstdint>
#include <elf.h>

class section {
public:
    section(void *elf);

private:
    void HeaderInfo();
    std::string NameStr(uint32_t idx);
    std::string TypeStr(uint32_t type);

    // ELF base address,所有的偏移是基于elf的baseaddres计算的
    uint8_t *m_baseaddr;

    // Section Header的信息
    Elf64_Shdr *m_header;
    uint32_t m_shnum;
    std::map<std::string, uint32_t> m_sname_id;

    // String Table：
    char *m_shstrtab;
    char *m_strtab;
    char *m_symtab;
};