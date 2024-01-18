/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#include <cstdio>

#include "fatbinary.hpp"

using namespace cuda;

#define _CUDA_FAT_MAGIC     0x466243b1

FatBinary::FatBinary(void *fatCubin) {
    m_wrapper = (Wrapper *)fatCubin;
    if ((m_wrapper->magic != _CUDA_FAT_MAGIC) || (m_wrapper->version != 1)) {
        printf("Error check fatbinary->magic\n");
        return ;
    }

    if (m_wrapper->pCOB == 0) {
        printf("Error check fatbinary->binary\n");
        return;
    }

    // fatbin 通过clang_offload_bundle 工具封装了多个objects。
    m_bundle = new ClangOffloadBundle((void *)m_wrapper->pCOB);
}

DeviceFunc *FatBinary::GetDeviceFunc(char *funcname) {
    return m_bundle->GetDeviceFunc(funcname);
}