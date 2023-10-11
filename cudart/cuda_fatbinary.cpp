/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#include <cstdio>
#include <cstring>

#include "cuda_fatbinary.hpp"

using namespace cuda;

FatBinary::FatBinary(void *fatCubin) {
    __fatDeviceText *fatDeviceText = (__fatDeviceText *)fatCubin;
    COB_header *cob = (COB_header *)fatDeviceText->pCOB;
    printf("cob.magic: %s\n", cob->magic_string);
    printf("cob.entries_n: %ld\n", cob->entries_num);
    bundle_entry *next_entry = (bundle_entry *)cob->entries;
    uint32_t next_entry_size = sizeof(bundle_entry) + next_entry->entry_id_length;
    const char *target_entry_id = "hip-riscv64-unknown-linux-gnu-rv64gELF";

    for (uint32_t i=0; i<cob->entries_num; i++) {
        bundle_entry *entry = next_entry;
        uint32_t entry_size = next_entry_size;
            
        printf("### Entry Info: \n");
        printf("entry.object_offset: %lx\n", entry->code_object_offset);
        printf("entry.object_size: %lx\n", entry->code_object_size);   
        printf("entry.id_len: %ld\n", entry->entry_id_length);
        printf("entry.id: %s\n", (char *)entry->entry_id);
        printf("entry size: %x\n", entry_size);

        if (strncmp(target_entry_id, (const char *)entry->entry_id, entry->entry_id_length) == 0) {
            char *elf = (char *)fatDeviceText->pCOB + entry->code_object_offset;
            int  size = entry->code_object_size;

            elfs.push_back(new ELF(elf, size));
        }

        next_entry = (bundle_entry *)((uint64_t)entry + entry_size);
        next_entry_size = sizeof(bundle_entry) + next_entry->entry_id_length;
    }
}

uint64_t FatBinary::GetFunctionBin(char *funcname) {
    return 0;
}

uint32_t FatBinary::GetFunctionBinSize(char *funcname) {
    return 0;
}
