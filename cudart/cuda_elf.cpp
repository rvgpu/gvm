/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#include <iostream>
#include <cstring>

#include "cuda_elf.hpp"

using namespace cuda;

#include <cstdio>
ELF::ELF(void *elf, int size) {
    header = (Elf64_Ehdr *)elf;
    if(CheckMagic(header) == false) {
        std::cout << "Error to check elf file" << std::endl;
        return ;
    }
    
    // HeaderInfo(header);

    // Section Header List
    section_header = (Elf64_Shdr *)((uint64_t)header + header->e_shoff);

    // String Table Section index is header->e_shstrndx
    strtab_section_header = section_header + header->e_shstrndx;
    string_table = (char *)(strtab_section_header->sh_offset + uint64_t(header));

    // Get Symbol Table
    symtab_section_header = nullptr;
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

void *ELF::FindSymbol(char *fname) {
    uint32_t symsize = symtab_section_header->sh_size / symtab_section_header->sh_entsize;
    for (uint32_t i=0; i<symsize; i++) {
        Elf64_Sym sym = symbol_table[i];
        if (strcmp(SymbolName(sym.st_name), fname) == 0) {
            return (void *)(symbol_table + i);
        }
    }
    
    return NULL;
}

bool ELF::GetFunction(void *psym, uint64_t &bin, uint32_t &size) {
    Elf64_Sym *sym = (Elf64_Sym *)psym;
    bool ret = false;

    bin = 0;
    size = 0;

    if ((sym->st_info & 0xf) == STT_FUNC) {
        Elf64_Shdr *sh = section_header + sym->st_shndx;
        // SectionHeaderInfo(sh);

        uint64_t texaddr = sh->sh_offset + uint64_t(header);
        bin = texaddr + sym->st_value;
        size = sym->st_size;

        ret = true;
    }

    return ret;
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

void ELF::SectionHeaderInfo(void *header) {
    Elf64_Shdr *h = (Elf64_Shdr *)header;
    printf("Section header:\n");
    printf("Section Name:                       %s\n", SymbolName(h->sh_name));
    printf("Section Type:                       %d\n", h->sh_type);
    printf("Section flags:                      %ld\n", h->sh_flags);
    printf("Section addr:                       %ld\n", h->sh_addr);
    printf("Section offset:                     %ld\n", h->sh_offset);
}

char *ELF::SymbolName(uint32_t id) {
    return string_table + id;
}