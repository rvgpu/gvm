/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#include <vector>

#include "utils/macro.hpp"
#include "elf/elf.hpp"

namespace cuda {

class ClangOffloadBundle {
public:
    ClangOffloadBundle(void *binary);
    ~ClangOffloadBundle();

    DeviceFunc *GetDeviceFunc(char *funcname);

private:
    typedef struct {
        uint64_t        code_object_offset;     // Byte offset from beginning of bundled code object to 1st code object.
        uint64_t        code_object_size;       // Byte size of 1st code object.
        uint64_t        entry_id_length;        // Character length of bundle entry ID of code object.
        uint8_t         entry_id[0];            // Bundle entry ID of code object. This is not NUL terminated
    } bundle_entry ALIGNED(8);

    // header of Clang Offload Bundle
    typedef struct {
        uint8_t         magic_string[24];       // set to "__CLANG_OFFLOAD_BUNDLE__"
        uint64_t        entries_num;            // Number of bundle entries
        bundle_entry    entries[0];             // Bundle Entries
    } COB_header ALIGNED(8);

    std::vector<ELF *> elfs;
    
    void EntryInfo(bundle_entry *entry, uint32_t entry_size);
};

}