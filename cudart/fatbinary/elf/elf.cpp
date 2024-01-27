/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#include <iostream>
#include <cstring>
#include <cstdio>

#include "elf.hpp"

namespace cuda {
ELF::ELF(void *elf, int size) {
    if (isRVGPU(elf) == false) {
        std::cout << "Error to check elf file" << std::endl;
        return ;
    }
    
    // HeaderInfo(elf);
    m_section = new section(elf);
    m_program = new program(elf);

    auto md = m_program->GetNoteHeader();
    m_metadata = new metadata(md.first, md.second);
}

bool ELF::GetFunction(char *fname, uint64_t &bin, uint32_t &size) {
    return m_section->GetFunction(fname, bin, size);
}

void ELF::HeaderInfo(void *header) {
    Elf64_Ehdr *h = (Elf64_Ehdr *)header;
    printf("ELF header:\n");
    printf("Type:                               %d\n", h->e_type);
    printf("Machine:                            %d\n", h->e_machine);
    printf("Version:                            %d\n", h->e_version);
    printf("Entry point address:                0x%lx\n", h->e_entry);
    printf("Start of program headers:           0x%lx\n", h->e_phoff);
    printf("Start of section headers:           0x%lx\n", h->e_shoff);
    printf("Flags:                              0x%x\n", h->e_flags);
    printf("Size of this header:                %d\n", h->e_ehsize);
    printf("Size of program headers:            %d\n", h->e_phentsize);
    printf("Number of program headers:          %d\n", h->e_phnum);
    printf("Size of section headers:            %d\n", h->e_shentsize);
    printf("Number of section headers:          %d\n", h->e_shnum);
    printf("Section header string table index:  %d\n", h->e_shstrndx);
}

bool ELF::MagicIsELF(void *header) {
    // ELF的标识符为：7f 45 4c 46
    char elfmagic[] = {
        0x7f, 0x45, 0x4c, 0x46,
    };

    return (strncmp(elfmagic, static_cast<char *>(header), sizeof(elfmagic)) == 0);
}

bool ELF::isRVGPU(void *header) {
    Elf64_Ehdr *ehdr = (Elf64_Ehdr *)(header);

    if (MagicIsELF(header) == false) {
        return false;
    }

    // RVGPU的machine编号是259，这个并没有写入elf.h中，只在llvm中定义了
    if (ehdr->e_machine != 259) {
        return false;
    }

    return true;
}

}