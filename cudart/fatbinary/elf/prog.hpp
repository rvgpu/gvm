#pragma once

#include <map>
#include <string>
#include <cstdint>
#include <elf.h>

namespace cuda {

class program {
public:
    program(void *elf);
    std::pair<uint64_t, uint32_t> GetNoteHeader(void);
    
private:
    void ShowProgramHeader(Elf64_Phdr *ph);

    // ELF base address,所有的偏移是基于elf的baseaddres计算的
    uint8_t *m_baseaddr;
};

} // namespace cuda