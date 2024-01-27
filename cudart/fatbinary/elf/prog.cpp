#include <map>
#include <string>
#include <cstdint>
#include <elf.h>

#include "prog.hpp"

namespace cuda {


program::program(void *elf) {
    m_baseaddr = (uint8_t *)elf;
}

std::pair<uint64_t, uint32_t> program::GetNoteHeader(void) {
    auto ret = std::make_pair<uint64_t, uint32_t>(0, 0);
    Elf64_Ehdr *ehdr = (Elf64_Ehdr *)(m_baseaddr);
    Elf64_Phdr *phdr = (Elf64_Phdr *)(m_baseaddr + ehdr->e_phoff);

    // 从NOTE的program段内读取metadata
    for (uint32_t idx=0; idx<ehdr->e_phnum; ++idx) {
        Elf64_Phdr *ph = &phdr[idx];
        if (ph->p_type == PT_NOTE) {
            // ShowProgramHeader(ph);
            ret = std::make_pair<uint64_t, uint32_t>((uint64_t)m_baseaddr + ph->p_offset, ph->p_memsz);
            break;
        }
    }

    return ret;
}

void program::ShowProgramHeader(Elf64_Phdr *ph) {
    printf("Program Header:\n");
    printf("type: %x\n", ph->p_type);
    printf("flags: %x\n", ph->p_flags);
    printf("offset: %lx\n", ph->p_offset);
    printf("vaddr: %lx\n", ph->p_vaddr);
    printf("paddr: %lx\n", ph->p_paddr);
    printf("pfilesz: %lx\n", ph->p_filesz);
    printf("memsize: %lx\n", ph->p_memsz);
    printf("align: %lx\n", ph->p_align);
}

} // namespace cuda