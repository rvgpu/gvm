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
    bundle_entry *next_entry = (bundle_entry *)cob->entries;
    uint32_t next_entry_size = sizeof(bundle_entry) + next_entry->entry_id_length;
    const char *target_entry_id = "hip-riscv64-unknown-linux-gnu-rv64g-ELF";

    for (uint32_t i=0; i<cob->entries_num; i++) {
        bundle_entry *entry = next_entry;
        uint32_t entry_size = next_entry_size;
        // EntryInfo(entry, entry_size);

        if (strncmp(target_entry_id, (const char *)entry->entry_id, entry->entry_id_length) == 0) {
            char *elf = (char *)fatDeviceText->pCOB + entry->code_object_offset;
            int  size = entry->code_object_size;

            elfs.push_back(new ELF(elf, size));
        }

        next_entry = (bundle_entry *)((uint64_t)entry + entry_size);
        next_entry_size = sizeof(bundle_entry) + next_entry->entry_id_length;
    }
}

DeviceFunc *FatBinary::GetDeviceFunc(char *funcname) {
    DeviceFunc *ret = NULL;
    for (ELF *elf : elfs) {
        void *sym = elf->FindSymbol(funcname);
        if (sym) {
            uint64_t bin;
            uint32_t size;
            if (elf->GetFunction(sym, bin, size)) {
                ret = new DeviceFunc();
                ret->name = funcname;
                ret->binary = bin;
                ret->binsize = size;
            }
        }
    }

    return ret;
}

void FatBinary::EntryInfo(bundle_entry *entry, uint32_t entry_size) {
    printf("### Entry Info: \n");
    printf("entry.object_offset: %lx\n", entry->code_object_offset);
    printf("entry.object_size: %lx\n", entry->code_object_size);   
    printf("entry.id_len: %ld\n", entry->entry_id_length);
    printf("entry.id: %s\n", (char *)entry->entry_id);
    printf("entry size: %x\n", entry_size);
}
