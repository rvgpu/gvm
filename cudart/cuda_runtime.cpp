/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#include <cstdio>

#include "fat_binary.hpp"

#include "cuda_runtime.hpp"

using namespace cudart;

Runtime::Runtime() {

}

void ** Runtime::RegisterFatBinary(void *fatCubin) {
    __fatDeviceText *fatDeviceText = (__fatDeviceText *)fatCubin;
    COB_header *cob = (COB_header *)fatDeviceText->pCOB;
    printf("cob.magic: %s\n", cob->magic_string);
    printf("cob.entries_n: %ld\n", cob->entries_num);
    bundle_entry *next_entry = (bundle_entry *)cob->entries;
    uint32_t next_entry_size = sizeof(bundle_entry) + next_entry->entry_id_length;

    for (uint32_t i=0; i<cob->entries_num; i++) {
        bundle_entry *entry = next_entry;
        uint32_t entry_size = next_entry_size;

        printf("### Entry Info: \n");
        printf("entry.object_offset: %lx\n", entry->code_object_offset);
        printf("entry.object_size: %lx\n", entry->code_object_size);
        printf("entry.id_len: %ld\n", entry->entry_id_length);
        printf("entry.id: %s\n", (char *)entry->entry_id);
        printf("entry size: %x\n", entry_size);

        next_entry = (bundle_entry *)((uint64_t)entry + entry_size);
        next_entry_size = sizeof(bundle_entry) + next_entry->entry_id_length;
    }

    return NULL;
}
