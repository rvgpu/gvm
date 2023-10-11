/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#include <iostream>
#include <cstring>

#include "elf.h"
#include "elf.hpp"

using namespace cuda;

#include <cstdio>
ELF::ELF(void *elf, int size) {
    Elf64_Ehdr *header = (Elf64_Ehdr *)elf;
    if(CheckMagic(header) == false) {
        std::cout << "Error to check elf file" << std::endl;
        return ;
    }
    
    // HeaderInfo(header);

    // Section Header List
    Elf64_Shdr *section_header = (Elf64_Shdr *)((uint64_t)header + header->e_shoff);

    // String Table Section index is header->e_shstrndx
    Elf64_Shdr *strtab_section_header = section_header + header->e_shstrndx;
    string_table = (char *)(strtab_section_header->sh_offset + uint64_t(header));

    // Get Symbol Table
    Elf64_Shdr *symtab_section_header = nullptr;
    symbol_table = nullptr;
    for (uint32_t i=0; i<header->e_shnum; i++) {
        if (section_header[i].sh_type == SHT_SYMTAB) {
            symtab_section_header = section_header + i;
            symbol_table = (Elf64_Sym *)(symtab_section_header->sh_offset + uint64_t(header));
            break;
        }
    }
}

bool ELF::CheckMagic(void *header) {
    // 7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
    char elfmagic[] = {
        0x7f, 0x45, 0x4c, 0x46, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    return (strncmp(elfmagic, static_cast<char *>(header), 16) == 0);
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