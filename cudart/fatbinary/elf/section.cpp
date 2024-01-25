#include "section.hpp"

section::section(void *elf)
{
    m_baseaddr = (uint8_t *)elf;
    Elf64_Ehdr *ehdr = (Elf64_Ehdr *)(elf);
    m_header = (Elf64_Shdr *)(m_baseaddr + ehdr->e_shoff);
    m_shnum = ehdr->e_shnum;
    m_shstrtab = (char *)(m_baseaddr + m_header[ehdr->e_shstrndx].sh_offset);

    HeaderInfo();
}

void section::HeaderInfo() {
    printf("SECTION Info:\n");
    printf("           Name Type       Flags      Addr       Offset\n");
    for (uint32_t idx=0; idx<m_shnum; idx++) {
        Elf64_Shdr *h = &m_header[idx];
        printf("%15s %-8s 0x%-8lx 0x%-8lx 0x%-8lx\n", 
            NameStr(h->sh_name).c_str(), TypeStr(h->sh_type).c_str(), h->sh_flags, h->sh_addr, h->sh_offset);
    }
}

std::string section::NameStr(uint32_t idx) {
    return std::string(m_shstrtab + idx);
}

std::string section::TypeStr(uint32_t type) {
    std::string ret = "ERRTYPE";

    switch (type) {
    case SHT_NULL:              ret = "NULL";           break;  /* Section header table entry unused */
    case SHT_PROGBITS:          ret = "PROGBITS";       break;  /* Program data */
    case SHT_SYMTAB:            ret = "SYMTAB";         break;  /* Symbol table */
    case SHT_STRTAB:            ret = "STRTAB";         break;  /* String table */
    case SHT_RELA:              ret = "RELA";           break;  /* Relocation entries with addends */
    case SHT_HASH:              ret = "HASH";           break;  /* Symbol hash table */
    case SHT_DYNAMIC:           ret = "DYNAMIC";        break;  /* Dynamic linking information */
    case SHT_NOTE:              ret = "NOTE";           break;  /* Notes */
    case SHT_NOBITS:            ret = "NOBITS";         break;  /* Program space with no data (bss) */
    case SHT_REL:               ret = "REL";            break;  /* Relocation entries, no addends */
    case SHT_SHLIB:             ret = "SHLIB";          break;  /* Reserved */
    case SHT_DYNSYM:            ret = "DYNSYM";         break;  /* Dynamic linker symbol table */
    case SHT_INIT_ARRAY:        ret = "INIT_ARRAY";     break;  /* Array of constructors */
    case SHT_FINI_ARRAY:        ret = "FINI_ARRAY";     break;  /* Array of destructors */
    case SHT_PREINIT_ARRAY:     ret = "PREINIT_ARRAY";  break;  /* Array of pre-constructors */
    case SHT_GROUP:             ret = "GROUP";          break;  /* Section group */
    case SHT_SYMTAB_SHNDX:      ret = "SYMTAB_SHNDX";   break;  /* Extended section indices */
    case SHT_NUM:               ret = "NUM";            break;  /* Number of defined types.  */
    case SHT_LOOS:              ret = "LOOS";           break;  /* Start OS-specific.  */
    case SHT_GNU_ATTRIBUTES:    ret = "GNU_ATTRIBUTES"; break;  /* Object attributes.  */
    case SHT_GNU_HASH:          ret = "GNU_HASH";       break;  /* GNU-style hash table.  */
    case SHT_GNU_LIBLIST:       ret = "GNU_LIBLIST";    break;  /* Prelink library list */
    case SHT_CHECKSUM:          ret = "CHECKSUM";       break;  /* Checksum for DSO content.  */
    case SHT_LOSUNW:            ret = "LOSUNW";         break;  /* Sun-specific low bound.  */
    case SHT_SUNW_COMDAT:       ret = "SUNW_COMDAT";    break;
    case SHT_SUNW_syminfo:      ret = "SUNW_syminfo";   break;
    case SHT_GNU_verdef:        ret = "GNU_verdef";     break;  /* Version definition section.  */
    case SHT_GNU_verneed:       ret = "GNU_verneed";    break;  /* Version needs section.  */
    case SHT_GNU_versym:        ret = "GNU_versym";     break;  /* Version symbol table.  */
    case SHT_LOPROC:            ret = "LOPROC";	        break;  /* Start of processor-specific */
    case SHT_HIPROC:            ret = "HIPROC";         break;  /* End of processor-specific */
    case SHT_LOUSER:            ret = "LOUSER";         break;  /* Start of application-specific */
    case SHT_HIUSER:            ret = "HIUSER";         break;  /* End of application-specific */
    default:                    ret = "ERRTYPE";        break;
    }

    return ret;
}
