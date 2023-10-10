/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#ifndef __RVG_FATBINARY_H__
#define __RVG_FATBINARY_H__

#include <stdint.h>

#define ALIGNED(alignsize)  __attribute__((aligned(alignsize)))

// Structure of cuda_fatbin in ELF file
typedef struct {
    int32_t     m;                      // dont known now
    int32_t     v;                      // dont known now
    int64_t     pCOB;                   // pointer to clang offloat bundle
    int8_t      *f;                     // dont known now
} __fatDeviceText ALIGNED(8);


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

#endif // __RVG_FATBINARY_H__
