#include <map>
#include <string>
#include <cstdint>
#include <elf.h>

#include "utils/macro.hpp"

#include "metadata.hpp"

namespace cuda {

metadata::metadata(uint64_t addr, uint32_t size) {
    // Descriptor
    // Elf64_Nhdr *nhdr = (Elf64_Nhdr *)addr;
    // char *name = (char *)addr + sizeof(Elf64_Nhdr);
    // char *desc = (char *)addr + sizeof(Elf64_Nhdr) + ALIGN_SIZE_4(nhdr->n_namesz);
}


} // namespace cuda