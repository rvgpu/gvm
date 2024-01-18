/*
 * Copyright © 2023 Sietium Semiconductor.
 */
#include <cstdio>
#include <cstring>

#include "clang_offload_bundle.hpp"

namespace cuda {

constexpr char const* CLANG_OFFLOAD_BUNDLER_MAGIC_STR = "__CLANG_OFFLOAD_BUNDLE__";

/**
 * Format of Clang Offload Bundle
 * 
 * header +--------------------------+ 
 *        | MAGIC String             | 24 Bytes
 *        +--------------------------+  
 *        | Number of Bundle Entries | 8 Bytes
 *        +--------------------------+ <--------- 1st entry code object
 *        | entry.code_object_offset | 
 *        | entry.code_object_size   |
 *        | entry.id_length          |
 *        | entry.id[N]              |
 *        +--------------------------+ <--------- 2nd entry code object
 *        | entry.code_object_offset | 
 *        | entry.code_object_size   |
 *        | entry.id_length          |
 *        | entry.id[N]              |
 *        +--------------------------+
 *        | ......                   |
 *        +--------------------------+ <--------- Nth entry code object
 *        | entry.code_object_offset | 
 *        | entry.code_object_size   |
 *        | entry.id_length          |
 *        | entry.id[N]              |
 *        +--------------------------+
 *        | code objects data xxxxxx |
 *        | xxxxxxxxxxxxxxxxxxxxxxxx |
 *        | xxxxxxxxxxxxxxxxxxxxxxxx |
 *        +--------------------------+
 */

ClangOffloadBundle::ClangOffloadBundle(void *binary) {
    COB_header *cob = (COB_header *)binary;

    // 检查 MAGIC 是否为：CLANG_OFFLOAD_BUNDLER_MAGIC_STR
    if (strncmp((const char *)cob->magic_string, CLANG_OFFLOAD_BUNDLER_MAGIC_STR, 
                strlen(CLANG_OFFLOAD_BUNDLER_MAGIC_STR))) {
        printf("Error to check clang offload bundle magic\n");
        return ;
    }

    bundle_entry *next_entry = (bundle_entry *)cob->entries;
    uint32_t next_entry_size = sizeof(bundle_entry) + next_entry->entry_id_length;
    const char *target_entry_id = "hipv4-rvgpu-sietium-ss--r1000";

    for (uint32_t i=0; i<cob->entries_num; i++) {
        bundle_entry *entry = next_entry;
        uint32_t entry_size = next_entry_size;
        // EntryInfo(entry, entry_size);

        if (strncmp(target_entry_id, (const char *)entry->entry_id, entry->entry_id_length) == 0) {
            char *elf = (char *)binary + entry->code_object_offset;
            int  size = entry->code_object_size;

            elfs.push_back(new ELF(elf, size));
        }

        next_entry = (bundle_entry *)((uint64_t)entry + entry_size);
        next_entry_size = sizeof(bundle_entry) + next_entry->entry_id_length;
    }
}

ClangOffloadBundle::~ClangOffloadBundle() {

}

DeviceFunc *ClangOffloadBundle::GetDeviceFunc(char *funcname) {
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

void ClangOffloadBundle::EntryInfo(bundle_entry *entry, uint32_t entry_size) {
    printf("### Entry Info: \n");
    printf("entry.object_offset: %lx\n", entry->code_object_offset);
    printf("entry.object_size: %lx\n", entry->code_object_size);   
    printf("entry.id_len: %ld\n", entry->entry_id_length);
    printf("entry.id: %s\n", (char *)entry->entry_id);
    printf("entry size: %x\n", entry_size);
}

}